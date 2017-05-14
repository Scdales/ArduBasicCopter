# ArduBasicCopter

This is a basic program designed with an Arduino Uno to run a quadcopter/drone with 4 motors mounted in X formation.
This only offers basic throughput control and will not self stabilise.

## Drones can be dangerous!

<b>Once fitted with propellors and running at speed, some motors have enough power to chop fingers.
This program must be tested and tuned to function correctly with your transmitter before you can fit propellors.
Once you do, make sure to respect any local laws,
and stand well back :)</b>

## Things you need to get going

The basic hardware you will require is:
- A frame
- 4 Motors
- 4 ESCs (Electronic Speed Controllers) Rated depending on which motors and battery you chose. Around 20A should do.
- 3 or 4 cell lipo battery around 2000mAh. This will power the arduino and the motors.
- Control Transmitter & RF Receiver (You get these in pairs. Something similar to <a href="https://www.amazon.co.uk/Radiolink-Remote-Control-Transmitter-Receiver/dp/B00RCYAFTI/" target="_blank">this.</a> The only criteria is PWM (Pulse Width Modulation) output. SBUS and PPM does not currently work. This program only allows for 6 channels, but can be easily modified to allow for more.

The pin wirings for the different components are listed in lines 8 through 35 of ArduBasicCopter.ino, you can take them as a guide.
A multimeter will help you testing that components are powered and operating correctly. Do your research into each module and ensure compatibilty with the other components. There are many guides <a href="http://lmgtfy.com/?q=DIY+Drone">already available online</a>.

## Libraries

This program uses the PinChangeInt library to allow for more interrupts.
<a href="https://github.com/GreyGnome/PinChangeInt">https://github.com/GreyGnome/PinChangeInt</a>

## Things left on the todo list
- [x] Upload to Github
- [ ] PID Controllers for motors
- [ ] Gyroscope/Accelorometer functions for stabilising (i2c?)
- [ ] Self calibration functions
