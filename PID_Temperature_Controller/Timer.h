#ifndef Timer_h
#define Timer_h
#include <Arduino.h>

class Timer
{
  private:
    unsigned long prev = 0;
    unsigned long now;
    
    
  public:
    
    unsigned long interval;
    void reset();
    void update();
};

void Timer::update()
{
  interval = millis() - prev;
}

void Timer::reset()
{
  prev = millis();
}

#endif
