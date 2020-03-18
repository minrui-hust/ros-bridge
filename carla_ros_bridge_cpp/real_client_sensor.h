#pragma once
#include "client_sensor.h"
#include "real_actor.h"

namespace ros_bridge {

template <typename _Derived>
class RealClientSensor : public RealActor<_Derived>,
                         public ClientSensor<_Derived> {
 public:
 protected:
};

}  // namespace ros_bridge