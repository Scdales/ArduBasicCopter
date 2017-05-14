// PinChangeInt.h was included to allow for software interrupts

#include "MotorClass.h"
#include "ChannelClass.h"
#include "PinChangeInt.h"
#include <Servo.h>

//FRONT LEFT MOTOR OUTPIN PIN
#define MOTORFL 4
//INPUT READING PWM OFFSET
#define MOTORFLOFFSET 0

//FRONT RIGHT MOTOR OUTPIN PIN
#define MOTORFR 5
//INPUT READING PWM OFFSET
#define MOTORFROFFSET 0

//BACK LEFT MOTOR OUTPUT PIN
#define MOTORBL 6
//INPUT READING PWM OFFSET
#define MOTORBLOFFSET 0

//BACK RIGHT MOTOR OUTPUT PIN
#define MOTORBR 7
//INPUT READING PWM OFFSET
#define MOTORBROFFSET 0

// RADIO CONTROL INPUT PINS FROM RECEIVER
#define PITCH 9
#define YAW 8
#define THROTTLE 10
#define ROLL 11
#define KNOB_RIGHT 12
#define KNOB_LEFT 13

/*
 * These values are for setting the limits for each of your transmitters channels
 * Use the script in the /tools directory to view the output of each of the on-board receivers' PWM channels
 */
#define PITCHLOW 1340
#define PITCHHIGH 1502
#define PITCHMID 1648

#define THROTTLELOW 1180
#define THROTTLEMID 1502
#define THROTTLEHIGH 1824

#define ROLLLOW 1308
#define ROLLMID 1476
#define ROLLHIGH 1676

#define YAWLOW 1324
#define YAWMID 1500
#define YAWHIGH 1692

#define AUX1LOW 1000
#define AUX1MID 1500
#define AUX1HIGH 2010

#define AUX2LOW 1000
#define AUX2MID 1500
#define AUX2HIGH 2010


//VARIABLES
unsigned long time1;
unsigned long time2;
boolean startupFlag = false;
boolean loopEnable = false;
int tempPitch;
int tempYaw;
int tempRoll;

// Motors numbered 0 to 4 are front left, front right, back left, back right
Motor motors [] = {
  Motor(MOTORFL,MOTORFLOFFSET),Motor(MOTORFR,MOTORFROFFSET),
  Motor(MOTORBL,MOTORBLOFFSET),Motor(MOTORBR,MOTORBROFFSET)};

Channel channels [] = {
  Channel(PITCH,PITCHHIGH,PITCHMID,PITCHLOW),Channel(YAW,YAWLOW,YAWMID,YAWHIGH),
  Channel(THROTTLE,THROTTLELOW,THROTTLEMID,THROTTLEHIGH),
  Channel(ROLL,ROLLLOW,ROLLMID,ROLLHIGH),Channel(KNOB_LEFT,AUX1LOW,AUX1MID,AUX1HIGH),
  Channel(KNOB_RIGHT,AUX2LOW,AUX2MID,AUX2HIGH)};

int channelReading [5];

void channelFunc() {
  if (digitalRead(PCintPort::arduinoPin) == HIGH){
    if  (PCintPort::arduinoPin == THROTTLE) {
      channels[2].takeReading1(micros());
    }
    else if  (PCintPort::arduinoPin == PITCH) {
      channels[0].takeReading1(micros());
    }
    else if  (PCintPort::arduinoPin == YAW) {
      channels[1].takeReading1(micros());
    }
    else if  (PCintPort::arduinoPin == ROLL) {
      channels[3].takeReading1(micros());
    }
    else if  (PCintPort::arduinoPin == KNOB_LEFT) {
      channels[4].takeReading1(micros());
    }
    else if  (PCintPort::arduinoPin == KNOB_RIGHT) {
      channels[5].takeReading1(micros());
    }
  }
  else {
    if  (PCintPort::arduinoPin == THROTTLE) {
      channels[2].takeReading2(micros());
    }
    else if  (PCintPort::arduinoPin == PITCH) {
      channels[0].takeReading2(micros());
    }
    else if  (PCintPort::arduinoPin == YAW) {
      channels[1].takeReading2(micros());
    }
    else if  (PCintPort::arduinoPin == ROLL) {
      channels[3].takeReading2(micros());
    }
    else if  (PCintPort::arduinoPin == KNOB_LEFT) {
      channels[4].takeReading2(micros());
    }
    else if  (PCintPort::arduinoPin == KNOB_RIGHT) {
      channels[5].takeReading2(micros());
    }

  }
}

void setup() {
  Serial.begin(57600);
  //  Serial.end();

  for (int i=0;i<6;i++) {
    if (i<4) {
      motors[i].begin();
    }
    channels[i].begin();
    attachPinChangeInterrupt(channels[i].returnPin(), channelFunc, CHANGE);
  }
  while(true)
  {
    Serial.println("Starting...");
    time1 = millis();
    if (channels[2].throttleOut()>=770 || channels[2].throttleOut()<=650)
    {
      startupFlag = false;
    }
    else if (channels[2].throttleOut()<=770 && channels[2].throttleOut()>=650 && startupFlag == false)
    {
      time2 = millis();
      startupFlag = true;
    }
    else if (channels[2].throttleOut()<=770 && channels[2].throttleOut()>=650 && startupFlag == true && time1-time2 == 2000)
    {
      break;
    }
  }
  for (int i=0;i<4;i++) {
    motors[i].initialize();
  }

}

void loop() {
  
  int pitch = channels[0].reading();
  int yaw = channels[1].reading();
  int throttle = channels[2].throttleOut();
  int roll = channels[3].reading();
  //int knobLeft = channels[4].reading();
  //int knobRight = channels[5].reading();

  for (int i=0;i<4;i++) {   
    motors[i].speedAdjust(throttle);
  }

  motors[0].control(-pitch +yaw);
  motors[1].control(-yaw -roll);
  motors[2].control(-yaw +roll);
  motors[3].control(pitch +yaw);

  Serial.print("Motor 1: ");
  Serial.print(motors[0].status());
  Serial.print("  Motor 2: ");
  Serial.print(motors[1].status());
  Serial.print("  Motor 3: ");
  Serial.print(motors[2].status());
  Serial.print("  Motor 4: ");
  Serial.println(motors[3].status());

}

