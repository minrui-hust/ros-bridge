#pragma once
#include "client_sensor.h"
#include "pseudo_actor.h"

namespace ros_bridge {

template <typename _Derived>
class PseudoClientSensor : public PseudoActor<_Derived>,
                           public ClientSensor<_Derived> {
 public:
 protected:
};

}  // namespace ros_bridge