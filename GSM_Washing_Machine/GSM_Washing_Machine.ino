#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <GSM.h>

#define PINNUMBER ""
const byte relay = 13;

const byte ROWS = 4;
const byte COLS = 3;
byte rowPins[ROWS] = {5, 11, 9, 7};
byte colPins[COLS] = {10, 8, 6};

char keys[ROWS][COLS] = {
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);
LiquidCrystal_I2C lcd(0x3F, 16, 2);
GSM gsmAccess;
GSM_SMS sms;

char phoneNum[11];
bool started = 0;
bool finished = 0;

void setup() {
  lcd.begin();
  lcd.print("Connecting to");
  lcd.setCursor(0,1);
  lcd.print("GSM network...");

  boolean notConnected = true;
  while (notConnected) {
    if (gsmAccess.begin(PINNUMBER) == GSM_READY) {
      notConnected = false;
    }
    else {
      delay(1000);
    }
  }
  
  lcd.clear();
  lcd.print("Please set");
  lcd.setCursor(0,1);
  lcd.print("the timer.");
}

void loop() {
  if (digitalRead(relay)) {
    if (started) {lcd.clear(); lcd.print("Washing...");}
    else {getNum(); }
  }
  else if (started && not digitalRead(relay)) {
    lcd.clear();
    lcd.print("Finished.");

    sms.beginSMS(phoneNum);
    sms.print("Your laundry is ready.");
    sms.endSMS();
    
    delay(5000);
    started = 0;
  }
  else {
    lcd.clear(); 
    lcd.print("Please set");
    lcd.setCursor(0,1);
    lcd.print("the timer.");
  }
}

void getNum() {
  int i = 0;
  lcd.clear();
  lcd.print("Enter Phone No.");
  lcd.setCursor(0,1);
  lcd.cursor();
  while (not started) {
    char key = kpd.getKey();
    if (key) {
      if(key == '#' or i >= 10) {
        started = 1;
      }
      else if(key == '*') {
        i--;
        lcd.setCursor(i,1);
        lcd.print(' ');
        lcd.setCursor(i,1);
      }
      else {
        phoneNum[i] = key;
        lcd.setCursor(i,1);
        lcd.print(key);
        i++;
      }
    }
  }
  lcd.noCursor();
}

