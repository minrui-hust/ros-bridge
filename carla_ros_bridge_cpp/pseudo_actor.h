#pragma once

#include "actor_base.h"
#include "ros/ros.h"

namespace ros_bridge {

template <typename _Derived>
class PseudoActor : public ActorBase<_Derived> {
 public:
 protected:
};

}  // namespace ros_bridge