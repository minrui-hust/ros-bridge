#pragma once
#include "real_actor.h"
#include "server_sensor.h"

namespace ros_bridge {

template <typename _Derived>
class RealServerSensor : public RealActor<_Derived>,
                         public ServerSensor<_Derived> {
 public:
 protected:
};

}  // namespace ros_bridge