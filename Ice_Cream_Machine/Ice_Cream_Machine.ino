#include <LiquidCrystal.h>
#define pbA 2
#define pbB 3
#define pbC 4
#define motor 6
#define fast 255
#define slow 127
#define timer 5000 //how long to run, in milliseconds
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

bool mode = 0;
bool limit = 0;
int state = 0;

void select();
void operate();
void pause();
void finish();
void (*function[4]) ();

unsigned long _start;
unsigned long _pauseStart;
unsigned long elapsed;

void setup() {
	lcd.begin(16, 2);
	pinMode(pbA,INPUT);
	pinMode(pbB,INPUT);
	pinMode(pbC,INPUT);
	pinMode(motor, OUTPUT);

  function[0] = select;
  function[1] = operate;
  function[2] = pause;
  function[3] = finish;
}

void loop() {
	if ((state >=0)&&(state<=3)) {(*function[state])();}
}

void select() {
	lcd.setCursor(0,0);
	lcd.print("Select Mode:    ");
	lcd.setCursor(0,1);
	if (digitalRead(pbB)) {delay(200); mode = not mode;}
	if (mode) {lcd.print("          <FAST>");}
	else {lcd.print("          <SLOW>");}
	
	if (digitalRead(pbA)) {delay(200); _start = millis(); state = 1;}
}

void operate() {
	elapsed = millis()-_start;

  if (mode) {analogWrite(motor,fast);}
  else {analogWrite(motor,slow);}
  
	lcd.setCursor(0,0);
	lcd.print("Running...      ");

	timekeeping(timer-elapsed);
	
	if (digitalRead(pbA)) {delay(200); _pauseStart = millis(); state = 2;}
	if (elapsed > timer) {state = 3;}

}

void pause() {
	analogWrite(motor,0);
	
	lcd.setCursor(0,0);
	lcd.print("                ");
  lcd.setCursor(0,1); 
  lcd.print("       Paused   ");
	
	unsigned long pauseTime = millis() - _pauseStart;
	
	if (digitalRead(pbA)) {delay(200); _start += pauseTime; state = 1;}
  if (digitalRead(pbB)) {delay(200); state = 0;}
}

void finish() {
	if (digitalRead(pbC)) {analogWrite(motor,slow);}
	else {analogWrite(motor,0);}
	
	lcd.setCursor(0,0);
	lcd.print("                ");
  lcd.setCursor(0,1); 
  lcd.print("     Finished   ");
	
  if (digitalRead(pbA)) {delay(200); state = 0; analogWrite(motor,0);}
}

void timekeeping(unsigned long remain) {
	lcd.setCursor(0,1);
	lcd.print("           ");
	
	byte minutes = remain/60000;
	byte seconds = (remain%60000)/1000;
	if (minutes<10){lcd.print("0");lcd.print(minutes,DEC);}
	else {lcd.print(minutes,DEC);}
	lcd.print(":");
	if (seconds<10){lcd.print("0");lcd.print(seconds,DEC);}
	else{lcd.print(seconds,DEC);}
}

