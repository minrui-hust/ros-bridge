#pragma once
#include "actor.h"

namespace ros_bridge {

class EgoCar: public Actor {
 public:
  void Update() final;
};

}  // namespace ros_bridge