#ifndef IMU_HPP
#define IMU_HPP

#include <Util/util.hpp>

namespace IRL 
{
  
  enum DataType {
    MAG,
    ACCEL,
    GYRO.
    TEMP,
    PRESSURE
  };
  
  struct IMUData_t
  {
    DataType type;
    union
    {
      triple<float> magnetic;
      triple<float> acceleration;
      triple<float> gyro;
      float temperature;
      float pressure;
    };
  };
  
  class IMU 
  {
     ~IMU(){};
     virtual setup() = 0;
     virtual cleanup() = 0;
     
  };
}

#endif // IMU_HPP