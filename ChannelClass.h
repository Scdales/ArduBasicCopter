#ifndef ChannelClass_h
#define ChannelClass_h

#include "Arduino.h"

class Channel
{
  public:
  Channel(int pin,int low, int mid, int high);
  
  void begin();
  int returnPin();
  int reading();
  
  void takeReading1(unsigned long timer);
  void takeReading2(unsigned long timer);
  
  int throttleOut();
  
  private:
  
  int _pin;
  int _reading;
  
  int _low;
  int _mid;
  int _high;
  
  unsigned long _time1;
  unsigned long _time2;
  
  
};

#endif
