#ifndef Timer_h
#define Timer_h
#include <Arduino.h>

class Timer
{
	private:
		unsigned long prev = 0;
		unsigned long now;
		unsigned long interval;

	public:
		unsigned long get_interval();
		void reset();
};

unsigned long Timer::get_interval()
{
	interval = millis() - prev;
	return interval;
}

void Timer::reset()
{
	prev = millis();
}

#endif
