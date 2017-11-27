// SpeedControl
// by Andrew Kramer

// Provides speed control for a single DC motor
// uses PID control algorithm adapted from 
// Brett Beauregard's PID library for arduino

#include"Arduino.h"
#include"SpeedControl.h"


#define DEFAULT_MIN_SPEED 60
const double defaultGain = 1.0;

// accepts a pointer to a Motor and a pointer to an Encoder as parameters
// sets gains to 1.0 and minimum speed to 60 by default
SpeedControl::SpeedControl(Motor *motor, Encoder *encoder)
{
	_encoder = encoder;
	_motor = motor;
	_iTerm = 0;
	_pwm = 0;
	_lastSpeed = 0;

	_kP = defaultGain;
	_kI = defaultGain;
	_kD = defaultGain;

	_setPoint = 0; // in degrees/second, goal speed;
	_minSpeed = 0;

	_dir = 1;//suakii
	

}

// accepts three doubles as parameters
//   kP - the proportional gain
//   kI - the integral gain
//   kD - the derivative gain
// sets the PID gains to the given values
void SpeedControl::setGains(double kP, double kI, double kD)
{
	_kP = kP;
	_kI = kI;
	_kD = kD;
}

// accepts an int as a parameter
// sets the min speed to the given value
void SpeedControl::setMinSpeed(int minSpeed)
{
	_minSpeed = minSpeed;
}

// accepts an int, speed in degrees/second, as a parameter
// changes the set point to the abs(speed) if abs(speed) is
// above the min speed
// changes the set point to the min speed if abs(speed) is
// between min speed and 0
// sets motor direction to backward if speed is negative
// sets motor direction to freewheel if speed is 0
//suakii
// 모터의 스펙은 105rpm, 2100 pulses/1회전

void SpeedControl::setSpeed(int speed)
{
	if (speed < 0)
	{
		//_motor->setBack();//suakii
		speed *= -1;
		_dir = -1;//suakii
	}
	else if (speed > 0)
	{
		//_motor->setFwd();//suakii
		_dir = 1;
	}
	if (speed == 0)
	{
		_motor->setStop();//suakii
	}
	//if (speed < _minSpeed && speed > 0)//suakii
	//	speed = _minSpeed;

 
	_setPoint = speed;
}

// returns the distance rotated by the motor's output shaft in degrees
// since the last call to getDistance()
int SpeedControl::getDistance()
{
	return _encoder->getDistance();
}

// adjusts motor's PWM level to correct for any error between the
// set point and the actual speed of the motor's output shaft
// MUST be called regularly on the same deltaT used to calculate
// motor speed in the Encoder object
void SpeedControl::adjustPWM()
{
	int speed = _encoder->getSpeed(); // motor control returns vector speed;degrees/second
	if (speed < 0) speed *= -1;  // convert speed to scalar
	int error = _setPoint - speed;
	_iTerm += (_kI * (double)error);
	double dInput = speed - _lastSpeed;
	int adjustment = (_kP * (double)error) + _iTerm - (_kD * dInput);
	_pwm += adjustment;
	constrainPWM();
	if (_dir == 1)
		_motor->setFwd(_pwm);
	else if (_dir == -1)
		_motor->setBack(_pwm);
	
	_lastSpeed = speed;

}

void SpeedControl::constrainPWM()
{
	if (_pwm > 255) _pwm = 255;
	else if (_pwm < 0) _pwm = 0;
}


//delte below code and using encoder getSpeed
// to show pwm value return adustpwm value
int SpeedControl::getSpeed() 
{
	return _pwm;//this value is control motor's pwm : suakii
}
