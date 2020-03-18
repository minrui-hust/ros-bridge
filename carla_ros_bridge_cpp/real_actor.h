#pragma once
#include "actor_base.h"
#include "carla/client/Actor.h"

namespace ros_bridge {

using CarlaActorPtr = carla::SharedPtr<carla::client::Actor>;

template <typename _Derived>
class RealActor : public ActorBase<_Derived> {
 public:
 protected:
};

}  // namespace ros_bridge