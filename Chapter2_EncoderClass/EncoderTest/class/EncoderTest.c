/*
 * Encoder Test
 * suakii@gmail.com
 */

#include "class/Motor.h"
#include "class/Encoder.h"

#include <MsTimer2.h>

int encoderA = 2;
int encoderB = 4;
long deltaT = 50000;//millisecond
int ticksPerRev = 2100;
int motorPlus = 5;//아두이노5번핀 -- 모터 드라이버의 A-1A                      
int motorMinus = 6;//아두이노 6번핀 --모터 드라이버의 A-1B  
Motor lhMotor(motorPlus, motorMinus);
Encoder lhEncoder(encoderA, encoderB, deltaT,ticksPerRev);

int total =2100;//모터가 1회전 하기 위한 펄스 수                      
int motorSpeed = 200;//모터 구동 pwm value

void setup() {
    Serial.begin(115200);//시리얼로 값을 보내기 위한 작업
    attachInterrupt(0, readLHEncoder, CHANGE);
}
void loop() {
   
   lhMotor.setFwd(motorSpeed);
   int currentCount = lhEncoder.getCount();
   //Serial.println(currentCount);
    if (currentCount == total)
        lhMotor.setStop();
    else {
    if (currentCount > total) {
        lhMotor.setStop();
        Serial.println("aaa");
    }
    else if (currentCount < total) 
    lhMotor.setFwd(motorSpeed);
  } 
}

// updates the left hand encoder when a left hand encoder event is triggered
void readLHEncoder()
{
  lhEncoder.updateCount();
}
