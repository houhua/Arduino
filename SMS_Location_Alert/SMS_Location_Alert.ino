#include "Config.h"
#include "Functions.h"

void setup() 
{
  GPSSerial.begin(9600);
  Serial.begin(9600);
  
  while (1) 
  {
    if (gsmAccess.begin("") == GSM_READY) {break;} 
    else {delay(1000);}
  }
}

void loop() 
{ 
  timer.update();
  
  while (not updateGps(gps)) {;}

  if (origin_distance > radius and not msgSent)
  {
    sendMessage(1);
    msgSent = 1;
  }
  
  if (sms.available())
  {
    char senderNumber[20];
    sms.remoteNumber(senderNumber, 20);
    Serial.println(senderNumber);
    if (senderNumber == phoneNumber) 
    {
      sendMessage();
    }

    sms.flush();
  }
}


