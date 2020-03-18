#pragma once
#include "sensor_base.h"

namespace ros_bridge {

template <typename _Derived>
class ServerSensor : public SensorBase<_Derived> {};

}  // namespace ros_bridge