#include "MotorClass.h"
#include <Servo.h>

Motor::Motor(int pin, int offset)
{
  _pin = pin;
  _fixedOffset = offset;
  _variance = offset;
}

void Motor::begin()
{
  _ESC.attach(_pin);
  _ESC.writeMicroseconds(0);
}

void Motor::initialize()
{
  _ESC.writeMicroseconds(LOW_THROTTLE);
  _throttle = LOW_THROTTLE;
  _status = LOW_THROTTLE;
}

void Motor::control(int variance)
{
  if (variance+_fixedOffset <= _variance+RESOLUTION || variance+_fixedOffset >= _variance+RESOLUTION)
  {
    _ESC.writeMicroseconds(_throttle+variance+_fixedOffset);
    _variance = variance+_fixedOffset;
    _status = _throttle+_variance;  
  }

}
    

void Motor::speedAdjust(int setting)
{
  if (setting+_variance >= _status+RESOLUTION || setting+_variance <= _status-RESOLUTION) {
  _ESC.writeMicroseconds(setting+_variance);
  _throttle = setting;
  _status = setting+_variance;
  }
}

int Motor::status()
{
  return _status;
}

