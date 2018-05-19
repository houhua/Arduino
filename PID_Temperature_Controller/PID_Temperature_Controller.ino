#include <max6675.h>
#include "Pid.h"
#include "Timer.h"

#define setTemp 73.9
#define tempUpdateInterval 300
#define controllerUpdateInterval 3000
#define pwmInterval 10000

#define thermoDO 10
#define thermoCS 11
#define thermoCLK 12
#define vccPin 13
#define relay 8

double params[3] = {8,0,130};
double windup = 0.1;
float tempPrev[20];
double tempAvg;

Timer tempUpdateTimer;
Timer controllerUpdateTimer;
Timer pwmTimer;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
Pid pid(params);

bool state = 0;
signed long outputInterval = 0;

void setup() {
  pid.set(setTemp);
  pid.setWindup(windup);
  Serial.begin(9600);
  pinMode(vccPin, OUTPUT); digitalWrite(vccPin, HIGH);
  pinMode(relay,OUTPUT);

  Serial.println("PWM-based PID Temperature Controller");
  delay(500);

  for (int i = 0 ; i < 20; i++)
  {
    tempPrev[i] = thermocouple.readCelsius();
  }
}

void loop() {
  if (tempUpdateTimer.get_interval() > tempUpdateInterval)
  {
   float temp = thermocouple.readCelsius();
   float tempSum = 0;
   tempPrev[0] = temp;

   for (int i = 0 ; i < 20; i++)
   {
    if (i != 0) {tempPrev[20-i] = tempPrev[19-i];}
    tempSum += tempPrev[i];
   }

   tempAvg = tempSum /20;

   Serial.print("C = ");
   Serial.println(tempAvg);

   tempUpdateTimer.reset();
  }

  if (controllerUpdateTimer.get_interval() > controllerUpdateInterval)
  {
   double output = pid.update(tempAvg);

   outputInterval = output/70*-1*pwmInterval;
   controllerUpdateTimer.reset();
  }

  int pwmTime = pwmTimer.get_interval();

  if (pwmTime > outputInterval)
  {
    state = 0;
  }
  else
  {
    state = 1;
  }

  if (pwmTime > pwmInterval)
  {
   pwmTimer.reset();
  }

  digitalWrite(relay, state);
}
