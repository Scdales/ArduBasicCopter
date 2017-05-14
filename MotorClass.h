#ifndef MotorClass_h
#define MotorClass_h
#define LOW_THROTTLE 600
#define RESOLUTION 6

#include "Arduino.h"
#include <Servo.h>


class Motor
{
  public:
  Motor(int pin,int offset);
  
  void begin();
  void initialize();
  void speedAdjust(int setting);
  int status();
  
  void control(int variance);

  private:
  
  Servo _ESC;
  int _pin;
  
  int _throttle;
  int _status;
  int _fixedOffset;
  int _variance;
};

#endif

