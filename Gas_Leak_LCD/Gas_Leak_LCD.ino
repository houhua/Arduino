#include <LiquidCrystal.h>

int sensor = 9;
int output = 8;

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

unsigned long previousMillis = 0;
int lcdState = LOW;

void setup()
{
pinMode(output,OUTPUT);
pinMode(sensor,INPUT);
lcd.begin(16, 2);
}

void loop()
{

if (not digitalRead(sensor)) {
  digitalWrite(output,HIGH);
  
  unsigned long currentMillis = millis();

  if((lcdState == HIGH) && (currentMillis - previousMillis >= 500))
  {
    lcdState = LOW;  // Turn it off
    previousMillis = currentMillis;  // Remember the time
    lcd.clear();
  }
  else if ((lcdState == LOW) && (currentMillis - previousMillis >= 600))
  {
    lcdState = HIGH;  // turn it on
    previousMillis = currentMillis;   // Remember the time
    lcd.setCursor(0, 0);
    lcd.print("WARNING!!!     ");
    lcd.setCursor(0, 1);
    lcd.print("GAS LEAKING!   ");
  }
}
else {
  digitalWrite(output,LOW);
  lcd.setCursor(0, 0);
  lcd.print("STATUS:         ");
  lcd.setCursor(0, 1);
  lcd.print("GAS CAN ON      ");
}
}
