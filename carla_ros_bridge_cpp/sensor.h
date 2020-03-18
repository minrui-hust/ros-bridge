#pragma once
#include "actor.h"
#include "carla/client/Sensor.h"
#include "carla/sensor/RawData.h"

namespace ros_bridge {

using SensorDataPtr = carla::SharedPtr<carla::sensor::SensorData>;
using CarlaSensorPtr = carla::SharedPtr<carla::client::Sensor>;

class Sensor : public Actor {
 public:
  template <typename _Derived>
  Sensor(ros::NodeHandle& nh, CarlaActorPtr carla_actor, const _Derived* tag)
      : Actor(nh, carla_actor, tag) {
    auto sensor =
        boost::static_pointer_cast<carla::client::Sensor>(carla_actor_);
    sensor->Listen(
        std::bind(&Sensor::HandleSensorData, this, std::placeholders::_1));
  }

  // Implement by derived class to handle the sensor data.
  // Derived Sensors should cast sensor_data to sensor dependent types
  // Note: This function may be call on multiple thread, make it thread-safe!
  virtual void HandleSensorData(SensorDataPtr sensor_data) = 0;

 protected:
};

}  // namespace ros_bridge