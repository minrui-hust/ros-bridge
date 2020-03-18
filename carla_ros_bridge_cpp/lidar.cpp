#include "lidar.h"

namespace ros_bridge {
void Lidar::HandleSensorData(SensorDataPtr sensor_data) {
  auto lidar_measurement =
      boost::static_pointer_cast<carla::sensor::SensorData>(sensor_data);

  // Todo Process lidar measurement
}

}  // namespace ros_bridge