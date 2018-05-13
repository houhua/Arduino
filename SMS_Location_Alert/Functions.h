#ifndef _Functions_H_
#define _Functions_H_

bool updateGps(TinyGPS &gps)
{
  while (GPSSerial.available())
  {
    char c = GPSSerial.read();
    if (gps.encode(c)) 
    {
      gps.f_get_position(&lat, &lon, &_);
      gps.get_datetime(&date, &time, &_);
      origin_distance = gps.distance_between(lat,lon,setLat,setLon);
      return true;
    }
  }
  return false;
}

void sendMessage(bool warning = 0) 
{
  int hours = time/1000000+8;
  int minutes = time/10000-(hours-8)*100;

/*  
  sms.beginSMS(phoneNumber);
  sms.print("\n");
  
  if (warning) 
  {
    sms.print("Tracker is out of set radius!");
    sms.print("\n");
  }
  
  sms.print("Latitude: ");
  sms.print(String(lat,5));
  sms.print("\n");
  sms.print("Longitude: ");
  sms.print(String(lon,5));
  sms.print("\n");
  sms.print("Date: ");
  sms.print(date);
  sms.print("\n");
  sms.print("Time: ");
  sms.print(hours);
  sms.print(":");
  if (minutes < 10) {sms.print("0");}
  sms.print(minutes);
  sms.print("\n");
  
  sms.endSMS();

*/

  if (warning) 
  {
    Serial.println("Tracker is out of set radius!");
  }
  Serial.print("Latitude: ");
  Serial.println(String(lat,5));
  Serial.print("Longitude: ");
  Serial.println(String(lon,5));
  Serial.print("Date: ");
  Serial.println(date);
  Serial.print("Time: ");
  Serial.print(hours);
  Serial.print(":");
  if (minutes < 10) {Serial.print("0");}
  Serial.println(minutes);
  Serial.println(origin_distance);
  
  delay(5000);
}

#endif
