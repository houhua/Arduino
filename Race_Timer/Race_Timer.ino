#include <LiquidCrystal_I2C.h>

#define startSensor 5
#define endSensor 6
#define restartButton 7

LiquidCrystal_I2C lcd(0x3F, 16, 2);

String disp = "00:00.000";
bool started = 0;
unsigned long prev = 0;

void setup()
{ 
   pinMode(startSensor,INPUT);
   pinMode(endSensor,INPUT);

   Serial.begin(9600);
   lcd.begin();
   lcd.setCursor(0,0);
   lcd.print("Let's Race!     ");
}

void loop()
{ 
   if (not digitalRead(startSensor)) 
   {
     lcd.setCursor(0,0);
     lcd.print("Race started!   ");
     prev = millis();
     started = 1;
   }
   if (not digitalRead(endSensor)) 
   {
     lcd.setCursor(0,0);
     lcd.print("Race ended!     ");
     started = 0;
   }
   if (digitalRead(restartButton))
   {
     started = 0;
     lcd.setCursor(0,0);
     lcd.print("Let's Race!     ");
     disp = "00:00.000";
   }
   
   if (started)
   {
     disp = getTime(millis()-prev);
   }
   else
   {
     ;
   }
   
   lcd.setCursor(0,1);
   lcd.print("       ");
   lcd.print(disp);
   Serial.println(disp);
}

String getTime(unsigned long tick)
{
  String displayClock = "";
  int minutes = tick/60000;
  int seconds = (tick-(minutes*60000))/1000;
  int milliseconds = (tick-(minutes*60000)-(seconds*1000));
  
  if (minutes<10){displayClock += 0;}
  displayClock += minutes;
  displayClock += ":";
  if (seconds<10){displayClock += 0;}
  displayClock += seconds;
  displayClock += ".";
  if (milliseconds<100){displayClock += 0;}
  if (milliseconds<10){displayClock += 0;}
  displayClock += milliseconds;

  return displayClock;
}

