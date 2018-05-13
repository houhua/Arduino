#include <TinyGPS.h>
#include <GSM.h>
#include <AltSoftSerial.h>
#include "Timer.h"

#define setLat 1.5056487
#define setLon 103.8234438
#define radius 700.00

char phoneNumber[20] = "+60146961109";

AltSoftSerial GPSSerial(8, 9);
TinyGPS gps;
GSM gsmAccess;
GSM_SMS sms;
Timer timer;

bool msgSent = 0;
float lat, lon, origin_distance;
unsigned long date, time;
unsigned long _;
