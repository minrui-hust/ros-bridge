#include "camera.h"

namespace ros_bridge {

void Camera::HandleSensorData(SensorDataPtr sensor_data) {
    auto image = boost::static_pointer_cast<carla::sensor::SensorData>(sensor_data);

    // TODO process the image

}

}  // namespace ros_bridge