/*
 * Speed Test wit PID
 * class를 사용하지 않는 형태임 
 * 다음 작업에서는 클래스를 사용한 형태로 변환
 * suakii@gmail.com
 * 아래 코드 중 pid 제어부분과 switch 부분은
 * [canDynamix] 모터 속도 테스트  (광주로봇동호회_[깡통로봇연구소]) |작성자 Baram
*  코드를 참고하여 작성하였음을 밝힙니다.
 */
//arduino pid library
//https://playground.arduino.cc/Code/PIDLibrary
#include "src/PID_v1.h"

int pulses, currentPulses;
int motorSpeed;
    
int encoderA = 2;//아두이노2번핀 -- 모터의 3번핀 Encoder A Phase
int encoderB = 4;//아두이노4번핀 --- 모터의 4번핀 Encoder B Phase
int motorPlus = 5;//아두이노5번핀 -- 모터 드라이버의 A-1A                      
int motorMinus = 6;//아두이노 6번핀 --모터 드라이버의 A-1B  

int state = 0;
unsigned long pre_time = millis();
unsigned long pre_time_log = millis();
unsigned long pre_time_delay = millis();
int  pwm = 0;//motor pwm valuf for control

double enc_speed, goal_speed, pwm_output;
double Kp=30, Ki=20, Kd=0;
//PID(&Input, &Output, &Setpoint, Kp, Ki, Kd, Direction)
PID motorPID(&enc_speed, &pwm_output, &goal_speed, Kp, Ki, Kd, DIRECT);




void setup() {
  pinMode(encoderA, INPUT_PULLUP);//인코더 값을 읽기 위하여 내부 풀업 저항 사용 
  pinMode(encoderB, INPUT_PULLUP);
 
  
  attachInterrupt(0, A_CHANGE, CHANGE);//
   
  analogWrite(motorPlus, 0);//초기 모터 정지
  analogWrite(motorMinus, 0);
 
  Serial.begin(115200);//시리얼로 값을 보내기 위한 작업
  motorPID.SetSampleTime(10);
  motorPID.SetOutputLimits(0, 255);
  motorPID.SetMode(AUTOMATIC);
  goal_speed = 0;

}
bool pulsesChanged = false;

void loop() {

  /*
  2초마다 goal speed 를 증가시키고 있음.
  */
   switch(state)
  {
    case 0:
      if (millis()-pre_time_delay >= 2000)
      {
        pre_time_delay = millis();
        state = 1;
        goal_speed = 5;
      }
      break;

    case 1:
      if (millis()-pre_time_delay >= 2000)
      {
        pre_time_delay = millis();
        state = 2;
        goal_speed = 10;
      }
      break;

    case 2:
      if (millis()-pre_time_delay >= 2000)
      {
        pre_time_delay = millis();
        state = 3;
        goal_speed = 15;
      }
      break;
    case 3:
      if (millis()-pre_time_delay >= 2000)
      {
        pre_time_delay = millis();
        state = 4;
        goal_speed = 20;
      }
      break;
    case 4:
     if (millis()-pre_time_delay >= 2000)
      {
        pre_time_delay = millis();
        state = 5;
       goal_speed = 25;
      }
      break;
       case 5:
      if (millis()-pre_time_delay >= 2000)
      {
        pre_time_delay = millis();
        state = 0;
        goal_speed = 0;  
      }
      break;    
  }
  //pid input value 
  //현재 속도가 다시 pid로 들어감.
  enc_speed = motorSpeed;
  
  //pip에서 연산 후 ouput 값을 가지고 실제 모터 컨트롤
  if (motorPID.Compute() == true)
  {
    pwm = constrain(pwm_output, 0, 255);
    analogWrite(motorPlus, pwm);//계산된 값을 적용
  }
	//이전과 다르게 10ms 당 속도를 측정하고 있음.
  // pid의 계산시간 역시 10ms로 맞추어져 있음.
	if (millis()-pre_time >= 10)
  {
    pre_time = millis();
	  motorSpeed = pulses - currentPulses;//속도의 정의를 10ms당 회전수로 정의
	  currentPulses = pulses;    
  }

   //pwm 적용된 결과를 보기 위하여 100ms 마다 시리얼로 값을 전송
  if (millis()-pre_time_log >= 100)
  {
    pre_time_log = millis();
    Serial.print(goal_speed);
    Serial.print("  ");
    Serial.println(motorSpeed);
  }
  
}

void A_CHANGE() {                                     
  if ( digitalRead(encoderB) == 0 ) {
    if ( digitalRead(encoderA) == 0 ) {
      // A fall, B is low
      pulses--; // Moving forward
    } else {
      // A rise, B is high
      pulses++; // Moving reverse
    }
  } else {
    if ( digitalRead(encoderA) == 0 ) {
      pulses++; // Moving reverse
    } else {
      // A rise, B is low
      pulses--; // Moving forward
    }
  }
  pulsesChanged = true;

}



