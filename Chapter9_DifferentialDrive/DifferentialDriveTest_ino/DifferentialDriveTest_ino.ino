/*

   Encoder  speed Test using Class

   suakii@gmail.com
*/

#include "DifferentialDrive.h"
//#include <TimerOne.h>
#include "src/FlexiTimer2.h"


int encoderA = 2;
int encoderB = 4;
int encoderC = 3;
int encoderD = 7;

long deltaT = 10000 ;//microsecond - 10milli second
int ticksPerRev = 2100;
int motorPlus = 5;//아두이노5번핀 -- 모터 드라이버의 A-1A
int motorMinus = 6;//아두이노 6번핀 --모터 드라이버의 A-1B
int motorPlus2 = 9;//아두이노9번핀 -- 모터 드라이버의 B-1A
int motorMinus2 = 10;//아두이노 0번핀 --모터 드라이버의 B-1B


Motor lhMotor(motorPlus, motorMinus);
Encoder lhEncoder(encoderA, encoderB, deltaT, ticksPerRev);
SpeedControl lhSpeedControl(&lhMotor, &lhEncoder);
PositionControl lhPosition(&lhSpeedControl);


Motor rhMotor(motorPlus2, motorMinus2);
Encoder rhEncoder(encoderC, encoderD, deltaT, ticksPerRev);
SpeedControl rhSpeedControl(&rhMotor, &rhEncoder);
PositionControl rhPosition(&rhSpeedControl);

int wheelCirc = 34;
int wheelDist = 100;
double x, y;
double theta;




DifferentialDrive colin(&lhPosition, &rhPosition, 
  wheelCirc, wheelDist);


int state = 0;
int myTime = 2000;//2seconds
unsigned long pre_time = millis();
unsigned long pre_time_log = millis();
unsigned long pre_time_delay = millis();
int goalSpeed = 0;//degrees/sec
int currentSpeed = 0;

void setup() {
  Serial.begin(115200);//시리얼로 값을 보내기 위한 작업

  attachInterrupt(digitalPinToInterrupt(encoderA), readLHEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderC), readRHEncoder, CHANGE);

  
  FlexiTimer2::set(10, adjust);//milli seconds 
  FlexiTimer2::start();  

  lhSpeedControl.setGains(3.0, 0.2, 0.0);
  rhSpeedControl.setGains(3.0, 0.2, 0.0);
  
  goalSpeed = 0;
}
void loop() {
  double x, y, theta;
  colin.getPosition(x, y, theta);
  Serial.print(x);
  Serial.print(" ");
  Serial.print(y);
  Serial.print(" ");
  Serial.println(theta);
  

  if (Serial.available()) {
    char ch;
    ch = Serial.read();
    if (ch == 'w') {
      colin.drive(10,0);
    }
    else if (ch == 'x') {
      colin.drive(-10,0);
    }
    else {
      colin.drive(0,0);
    }
  }
  delay(100);
  /*
  colin.drive(10,0);

  delay(5000);

  
  colin.drive(-10,0);
  delay(5000);
  
  colin.drive(0,0);
  delay(5000);
  

  while(1);
  */

}

// updates the left hand encoder when a left hand encoder event is triggered
void readLHEncoder()
{
  lhEncoder.updateCount();
}

void readRHEncoder()
{
  rhEncoder.updateCount();
  
}

void adjust()
{
  colin.update();
}





