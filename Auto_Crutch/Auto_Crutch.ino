#define upperlimit 2
#define lowerlimit 3
#define toggle 4
#define motor 5
#define dirA 6
#define dirB 7
#define trig 13
#define echo 12
#define setDistance 200

bool rotate = 0;
bool dir = 0;

void setup() {
  pinMode(upperlimit,INPUT_PULLUP);
  pinMode(lowerlimit,INPUT_PULLUP);
  pinMode(toggle,INPUT_PULLUP);
  pinMode(motor,OUTPUT);
  pinMode(dirA,OUTPUT);
  pinMode(dirB,OUTPUT);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  Serial.begin(9600);
}

void loop() {
  bool extend = not digitalRead(toggle);
  if(extend)
  {
    dir = 1;
    
    double distance = ping();
    if (distance < setDistance or not digitalRead(upperlimit)) {rotate = 0;}
    else {rotate = 1;}
  }
  else 
  {
    dir = 0;
    if (not digitalRead(lowerlimit)) {rotate = 0;}
    else {rotate = 1;}
  }

  if (dir)
  {
    digitalWrite(dirA, 1);
    digitalWrite(dirB, 0);
  }
  else
  {
    digitalWrite(dirA, 0);
    digitalWrite(dirB, 1);
  }

  if (rotate) {digitalWrite(motor,1);}
  else {digitalWrite(motor,0);}
}

double ping() {
  double avgDistance = 0;
  for (int i = 0 ; i < 2; i++)
  {
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    unsigned long duration = pulseIn(echo, HIGH);
    // Calculating the distance
    double distance= duration*0.034/2;
    avgDistance += distance;
  }
  avgDistance = avgDistance / 3;
  Serial.println(avgDistance);
  return avgDistance;
}

