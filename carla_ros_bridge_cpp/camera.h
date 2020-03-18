#pragma once
#include "sensor.h"
#include "sensor_msgs/Image.h"

namespace ros_bridge {
class Camera : public Sensor {
  using RosMessage = sensor_msgs::Image;

 public:
  Camera(ros::NodeHandle& nh, CarlaActorPtr carla_actor)
      : Sensor(nh, carla_actor, this) {}

  virtual void HandleSensorData(SensorDataPtr sensor_data) final;

 protected:
};
}  // namespace ros_bridge