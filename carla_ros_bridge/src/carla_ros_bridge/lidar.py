#!/usr/bin/env python

#
# Copyright (c) 2018-2019 Intel Corporation
#
# This work is licensed under the terms of the MIT license.
# For a copy, see <https://opensource.org/licenses/MIT>.
#
"""
Classes to handle Carla lidars
"""

import threading

import numpy, math

import tf

from sensor_msgs.point_cloud2 import create_cloud_xyz32

from carla_ros_bridge.sensor import Sensor
import carla_ros_bridge.transforms as trans


class Lidar(Sensor):

    """
    Actor implementation details for lidars
    """

    def __init__(self, carla_actor, parent, communication, synchronous_mode):
        """
        Constructor

        :param carla_actor: carla actor object
        :type carla_actor: carla.Actor
        :param parent: the parent of this
        :type parent: carla_ros_bridge.Parent
        :param communication: communication-handle
        :type communication: carla_ros_bridge.communication
        """
        super(Lidar, self).__init__(carla_actor=carla_actor,
                                    parent=parent,
                                    communication=communication,
                                    synchronous_mode=synchronous_mode,
                                    prefix='lidar/' + carla_actor.attributes.get('role_name'))

        # store the disordered lidar measurement
        self.required_scan = 0
        self.received_lidar_data = {}
        self.aggregated_lidar_data = []
        self.aggregated_angle = 0
        self.max_delay = 3

        # used for multi-thread syncronization
        self.mutex = threading.Lock()

    def get_ros_transform(self, transform=None):
        """
        Function (override) to modify the tf messages sent by this lidar.

        The lidar transformation has to be altered:
        for some reasons lidar sends already a rotated cloud,
        so herein, we need to ignore pitch and roll

        :return: the filled tf message
        :rtype: geometry_msgs.msg.TransformStamped
        """
        tf_msg = super(Lidar, self).get_ros_transform(transform)

        rotation = tf_msg.transform.rotation
        quat = [rotation.x, rotation.y, rotation.z, rotation.w]
        dummy_roll, dummy_pitch, yaw = tf.transformations.euler_from_quaternion(
            quat)
        # set roll and pitch to zero
        quat = tf.transformations.quaternion_from_euler(0, 0, yaw)
        tf_msg.transform.rotation = trans.numpy_quaternion_to_ros_quaternion(
            quat)
        return tf_msg

    # pylint: disable=arguments-differ
    def sensor_data_updated(self, carla_lidar_measurement):
        """
        Function to transform the a received lidar measurement into a ROS point cloud message

        :param carla_lidar_measurement: carla lidar measurement object
        :type carla_lidar_measurement: carla.LidarMeasurement
        """

        # this function may be executed on different thread
        self.mutex.acquire()
        
        #header = self.get_msg_header(timestamp=stamp)
        header = self.get_msg_header()

        # convert the raw data into numpy
        lidar_data = numpy.frombuffer(
            carla_lidar_measurement.raw_data, dtype=numpy.float32)
        lidar_data = numpy.reshape(
            lidar_data, (int(lidar_data.shape[0] / 3), 3))
        # we take the oposite of y axis
        # (as lidar point are express in left handed coordinate system, and ros need right handed)
        # we need a copy here, because the data are read only in carla numpy
        # array
        lidar_data = -lidar_data
        # we also need to permute x and y
        lidar_data = lidar_data[..., [1, 0, 2]]

        # check the scan id if is we want
        scan = carla_lidar_measurement.scan
        scan_angle = carla_lidar_measurement.horizontal_end_angle - carla_lidar_measurement.horizontal_angle
        if self.required_scan ==0 or len(self.received_lidar_data) > self.max_delay:
            self.required_scan = scan + 1
            self.aggregated_lidar_data = [lidar_data]
            self.aggregated_angle = scan_angle
            self.received_lidar_data = {}
            print("drop")
        elif self.required_scan == scan:
            self.required_scan = scan + 1 # set required scan to next scan
            self.aggregated_lidar_data.append(lidar_data) # append current scan
            self.aggregated_angle += scan_angle
        else:
            self.received_lidar_data[scan] = (scan_angle, lidar_data) # store current frame for later use
        
        # we should publish if the aggregated angle is close 2pi
        should_publish = True
        while self.aggregated_angle < math.pi*2 - math.radians(3):
            if self.received_lidar_data.has_key(self.required_scan):
                (history_scan_angle, history_lidar_data) = self.received_lidar_data.pop(self.required_scan)
                self.aggregated_lidar_data.append(history_lidar_data)
                self.aggregated_angle += history_scan_angle
                self.required_scan += 1
            else:
                should_publish = False
                break

        #print(scan, scan_angle, len(self.received_lidar_data), len(self.aggregated_lidar_data))
        
        # if enough data aggregated, send it
        if should_publish:
            point_cloud_msg = create_cloud_xyz32(header, numpy.vstack(self.aggregated_lidar_data))
            self.publish_message(self.get_topic_prefix() + "/point_cloud", point_cloud_msg)
            self.aggregated_angle = 0
            self.aggregated_lidar_data = []

        # release the lock so other thread may call this function
        self.mutex.release()
