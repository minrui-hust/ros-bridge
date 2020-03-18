#pragma once
#include "carla/sensor/data/LidarMeasurement.h"
#include "real_server_sensor.h"
#include "sensor_msgs/PointCloud2.h"

namespace ros_bridge {

class Lidar : public RealServerSensor<Lidar> {
  public:
 protected:
};

}  // namespace ros_bridge