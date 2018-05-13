#define gain 0.1
#define voltage 240
#define minCharge 3.00
#define messageFrequency 864000000
#define PINNUMBER ""

#include<LiquidCrystal.h>
#include<GSM.h>

char phoneNumber[11] = "0146961109";

LiquidCrystal lcd (12,11,5,4,3,2);

GSM gsmAccess;
GSM_SMS sms;

unsigned int timesMessaged = 0;
double wattage = 0;
unsigned long prev = 0;

void setup()
 {
   Serial.begin(9600);
   lcd.begin(16 , 2);
   lcd.print("Connecting GSM..");

   boolean notConnected = false;
   while(notConnected)
   {
    if(gsmAccess.begin(PINNUMBER)==GSM_READY)
      notConnected = false;
    else
    {
      Serial.println("Not connected");
      delay(1000);
    }
   }

   lcd.clear();
   lcd.print("Unit(kWh):  0.00");
   lcd.setCursor(0,1);
   lcd.print("Cost(RM):   0.00");
 }

void loop()
 {
   if (millis()==prev) {;}
   else {
   updateWattage();
   double cost = calcCost();

   Serial.print(wattage);
   Serial.print(",");
   Serial.println(cost);

   updateLCD(wattage,cost);

   if (millis()>messageFrequency*(1+timesMessaged))
   {
      sendSms(wattage,cost);
      timesMessaged += 1;
   }

   prev = millis();
   }
}

double updateWattage()
{
   double reading = analogRead(A0);
   reading = reading - 512;
   reading = reading / (millis()-prev) * gain;
   double current = abs(reading);

   wattage += current * voltage / 3600000;
   return wattage;
}

double calcCost()
{
   double tariff = 0;
   if (wattage <= 200) {tariff = 0.218;}
   else if (wattage > 200 and wattage <= 300) {tariff = 0.334;}
   else if (wattage > 300 and wattage <= 600) {tariff = 0.516;}
   else if (wattage > 600 and wattage <= 900) {tariff = 0.546;}
   else {tariff = 0.571;}

   double cost = minCharge + (wattage * tariff);
   return cost;
}

void sendSms(double a, double b)
{
sms.beginSMS(phoneNumber);
sms.print("You have used wattage of ");
sms.print(a,2);
sms.print("kWh. ");
sms.print("Your estimated cost for this month is RM");
sms.print(b,2);
sms.print(".");
sms.endSMS();
}

void updateLCD(double a, double b)
{
   int aPos = 12;
   int bPos = 12;
   if (a >= 10) aPos -= 1;
   if (b >= 10) bPos -= 1;
   if (a >= 100) aPos -= 1;
   if (b >= 100) bPos -= 1;

   lcd.setCursor(aPos,0);
   lcd.print(a,2);
   lcd.setCursor(bPos,1);
   lcd.print(b,2);
}
