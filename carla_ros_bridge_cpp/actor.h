#pragma once
#include "carla/client/Actor.h"
#include "pseudo_actor.h"

namespace ros_bridge {

using CarlaActorPtr = carla::SharedPtr<carla::client::Actor>;

class Actor : public PseudoActor {
 public:
  template <typename _Derived>
  Actor(ros::NodeHandle& nh, CarlaActorPtr carla_actor, const _Derived* tag)
      : PseudoActor(nh), carla_actor_(carla_actor, tag) {}

  void Update() override {}

 protected:
  CarlaActorPtr carla_actor_;
};

}  // namespace ros_bridge