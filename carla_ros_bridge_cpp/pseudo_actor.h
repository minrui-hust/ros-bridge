#pragma once

#include "ros/ros.h"

namespace ros_bridge {

class PseudoActor {
 public:
  template <typename _Derived>
  PseudoActor(ros::NodeHandle &nh, const _Derived *tag) : nh_(nh) {
    pub_ =
        nh_.advertise<_Derived::RosMessage>(GetTopicPrefix() + "pointcloud", 1);
  }

  virtual void Update() = 0;

  std::string GetTopicPrefix() { return "/carla/" + name_ + "/"; }

 protected:
  std::string name_;
  ros::NodeHandle &nh_;
  ros::Publisher pub_;
};

}  // namespace ros_bridge