// Motor.cpp
// by Andrew Kramer
// Provides low-level control of a the speed and direction of a single DC motor
// by means of a motor driver such as the TB6612FNG
// modified by Jonghwa Park(suakii@gmail.com)

#include "Arduino.h"
#include "Motor.h"

// accepts three ints as parameters: 
//    the pin numbers for the direction control pins
//    and the pin number of the pwm pin
// direction 5, 6
//
Motor::Motor(int motorPlus, int motorMinus)
{
    _motorPlus = motorPlus;
    _motorMinus = motorMinus;
    analogWrite(_motorPlus, LOW);//initial stop
	analogWrite(_motorMinus, LOW);
}
// sets the motor's direction to forward
void Motor::setFwd(int level)
{
	analogWrite(_motorPlus, level);
	analogWrite(_motorMinus, LOW);
}
// sets the motor's direction to backward
void Motor::setBack(int level)
{
	analogWrite(_motorPlus, LOW);
	analogWrite(_motorMinus, level);
}
// sets the motor to brake
void Motor::setStop()
{
	analogWrite(_motorPlus, LOW);
	analogWrite(_motorMinus, LOW);
}
