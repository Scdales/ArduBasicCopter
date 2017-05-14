#include "ChannelClass.h"
#include "PinChangeInt.h"

#define DEADZONE 16

Channel::Channel(int pin, int low, int mid, int high)
{
  _pin = pin;
  _low = low;
  _mid = mid;
  _high = high;
}

void Channel::begin()
{
  pinMode(_pin, INPUT_PULLUP);
}


void Channel::takeReading1(unsigned long timer)
{
    _time1 = timer;
}

void Channel::takeReading2(unsigned long timer)
{
    _time2 = timer;
    _reading = _time2 - _time1;
}

int Channel::reading()
{
  if (_reading >= 2200 || _reading <= 900){
    return 0;
  }
  else if (_reading-_mid <= DEADZONE && _reading-_mid >= -DEADZONE){
    return 0;
  }
  else{
    if (_reading-_mid <= -DEADZONE) {
      return _reading-_mid+DEADZONE;
    }
    else if (_reading-_mid >= DEADZONE) {
      return _reading-_mid-DEADZONE;
    }
  }
}

int Channel::returnPin()
{
  return _pin;
}

int Channel::throttleOut()
{
  if (_pin==10) {
    if (_reading >= _high+10 || _reading <= _low-10){
      return 0;
    }
    else {
      return(map(_reading,_low,_high,700,1900));
    }
  }
}
  
  
