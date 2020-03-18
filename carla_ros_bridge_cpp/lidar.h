#pragma once
#include "carla/sensor/data/LidarMeasurement.h"
#include "sensor.h"
#include "sensor_msgs/PointCloud2.h"

namespace ros_bridge {

class Lidar : public Sensor {
 public:
  using RosMessage = sensor_msgs::PointCloud2;
  
  Lidar(ros::NodeHandle& nh, CarlaActorPtr carla_actor)
      : Sensor(nh, carla_actor, this) {}

  virtual void HandleSensorData(SensorDataPtr sensor_data) final;

 protected:
};
}  // namespace ros_bridge