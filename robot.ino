
#include <SoftwareSerial.h>

#define LED 12

#define MLa 4
#define MLb 5
#define MRa 6
#define MRb 7

#define TRIG 9
#define ECHO 8

SoftwareSerial bt(10,11);

bool autoMode = false;
bool stepStarted = false;

unsigned long previousMillis = 0;

int step = 0;

int turn90 = 450;
int turn180 = 1150;

// ----------- FUNCTION PROTOTYPES -----------
void forward();
void backward();
void left();
void right();
void stop();
void deliveryRun();
long getDistance();

// ----------- SETUP -----------
void setup() {

  bt.begin(9600);

  pinMode(MLa, OUTPUT);
  pinMode(MLb, OUTPUT);
  pinMode(MRa, OUTPUT);
  pinMode(MRb, OUTPUT);

  pinMode(LED, OUTPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

// ----------- LOOP -----------
void loop() {

  if(bt.available()){

    char c = bt.read();

    if(c=='1'){
      autoMode = true;
      step = 0;
      stepStarted = false;
    }

    if(c=='0'){
      stop();
      autoMode = false;
    }

    if(!autoMode){
      if(c=='2') forward();
      if(c=='3') backward();
      if(c=='4') left();
      if(c=='5') right();
      if(c=='6') stop();
    }
  }

  if(autoMode){
    deliveryRun();
  }
}

// ----------- OBSTACLE -----------
long getDistance(){

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 30000);
  long distance = duration * 0.034 / 2;

  return distance;
}

// ----------- DELIVERY STATE MACHINE -----------

void deliveryRun(){

  static unsigned long stepStart = 0;
  static unsigned long stepDuration = 0;
  static bool running = false;

  long distance = getDistance();
  unsigned long now = millis();

  // ----- OBSTACLE -----
  if(distance > 0 && distance < 8){
    stop();
    running = false;
    return;
  }

  // ----- START NEW STEP -----
  if(!running){

    running = true;
    stepStart = now;

    switch(step){
      case 0: forward(); stepDuration = 2000; break;
      case 1: right();   stepDuration = turn90; break;
      case 2: forward(); stepDuration = 2500; break;
      case 3: digitalWrite(LED, HIGH); stepDuration = 6000; break;
      case 4: right();   stepDuration = turn180; break;
      case 5: forward(); stepDuration = 2500; break;
      case 6: left();    stepDuration = 850; break;
      case 7: forward(); stepDuration = 2000; break;
    }
  }

  // ----- STEP TIMER -----
  if(now - stepStart >= stepDuration){

    if(step == 3) digitalWrite(LED, LOW);

    stop();
    step++;
    running = false;

    if(step > 7){
      autoMode = false;
      step = 0;
    }
  }
}
  
// ----------- MOTOR FUNCTIONS -----------

void forward(){
  digitalWrite(MRb, HIGH);
  digitalWrite(MRa, LOW);
  digitalWrite(MLb, HIGH);
  digitalWrite(MLa, LOW);
}

void backward(){
  digitalWrite(MRb, LOW);
  digitalWrite(MRa, HIGH);
  digitalWrite(MLb, LOW);
  digitalWrite(MLa, HIGH);
}

void left(){
  digitalWrite(MRb, LOW);
  digitalWrite(MRa, HIGH);
  digitalWrite(MLa, LOW);
  digitalWrite(MLb, HIGH);
}

void right(){
  digitalWrite(MRb, HIGH);
  digitalWrite(MRa, LOW);
  digitalWrite(MLa, HIGH);
  digitalWrite(MLb, LOW);
}

void stop(){
  digitalWrite(MRb, LOW);
  digitalWrite(MRa, LOW);
  digitalWrite(MLb, LOW);
  digitalWrite(MLa, LOW);
}