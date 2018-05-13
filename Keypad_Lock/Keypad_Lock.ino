#include <Keypad.h>

int lock = 9;          //output pin on Arduino
int buzzer = 10;

char correct[4] = {'5','2','4','1'};	//set password
char final[4] = {'0','0','0','0'};		//initialize password
bool locked = 1;                      //state for locked or not

void keypad();							//initialize keypad
const byte ROWS = 4;
const byte COLS = 3;
byte rowPins[ROWS] = {8, 7, 6, 5};
byte colPins[COLS] = {4, 3, 2};
char keys[4][3] = { {'1','2','3'},
                    {'4','5','6'},
                    {'7','8','9'},
                    {'*','0','#'} };      
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  pinMode(lock, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
  digitalWrite(lock, HIGH);
}

void loop() {
  int chksum = 0;	//reset check sum to zero
  
  char key = kpd.getKey();
  if (key) {											//take keypad input
    for(int i=0; i<3;i++){ final[i] = final[i+1];}
    final[3] = key; 
  }
  
  while(Serial.available()) {							//take bt input
	for(int i=0; i<3;i++){ final[i] = final[i+1];}
    final[3] = Serial.read();
  }
  
  for(int i=0; i<4; i++) {if(final[i]==correct[i]) { chksum += 1;}}		//how many digit is correct

  if (final[3]=='*') {				//check for buzzer
	  digitalWrite(buzzer,HIGH);
	  delay(1000);
	  final[3] = '0';
  }
  else {
	  digitalWrite(buzzer,LOW); 
  }
  
  if(chksum == 4 and locked) {					// check for lock
    Serial.println("UNLOCKED");
    digitalWrite(lock, LOW);
    locked = 0;
  }
  else if (chksum != 4 and not locked){
    Serial.println("LOCKED");
    digitalWrite(lock, HIGH);
    locked = 1;
  }
  
  // FOR TESTING
  /*
  Serial.print(final[0]);Serial.print(final[1]);Serial.print(final[2]);Serial.print(final[3]);
  Serial.print(" | ");
  Serial.print(correct[0]);Serial.print(correct[1]);Serial.print(correct[2]);Serial.print(correct[3]);
  Serial.println(" ");
  */
}
