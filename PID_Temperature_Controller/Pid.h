#ifndef Pid_h
#define Pid_h
#include <Arduino.h>
#include "Timer.h"

class Pid
{
	private:
		Timer timer;
		double Kp = 0;
		double Ki = 0;
		double Kd = 0;

		double prevError = 0;
		double iTerm = 0;
		double windup = 20.0;
		double setpoint = 0;
		double output = 0;

		int interval = 0;

	public:
		Pid(double arr[3]);
		void set(double sp);
		void setWindup(double value);
		double update(double reading);
		double update_angle(double reading);
		void clearIterm(void);
};

Pid::Pid(double arr[3])
{
	Kp = arr[0];
	Ki = arr[1];
	Kd = arr[2];
}

void Pid::set(double sp)
{
	setpoint = sp;
}

void Pid::setWindup(double value)
{
	this->windup = value;
}

void Pid::clearIterm(void)
{
	this->iTerm = 0;
}

double Pid::update(double reading)
{
	interval = timer.get_interval();

	double error = reading - setpoint;

	iTerm += error;
	iTerm = min(windup,max(iTerm,-windup));

	double dTerm = error-prevError;
	prevError = error;

	output = Kp*error + Ki*iTerm + Kd*dTerm;
    /* Serial.print(error);
	Serial.print(",");
	Serial.print(iTerm);
	Serial.print(",");
	Serial.println(dTerm); */

	timer.reset();

	return output;
}

double Pid::update_angle(double reading)
{
	interval = timer.get_interval();
	double error = reading - setpoint;
	error = atan2(sin(error),cos(error));

	iTerm += error;
	iTerm = min(windup,max(iTerm,-windup));

	double dTerm = error-prevError;
	prevError = error;

	output = Kp*error + Ki*iTerm + Kd*dTerm;

	timer.reset();

	return output;
}

#endif
