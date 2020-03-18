#pragma once
#include "real_server_sensor.h"
#include "sensor_msgs/Image.h"

namespace ros_bridge {

class Camera : public RealServerSensor<Camera> {
 public:
 protected:
};

}  // namespace ros_bridge