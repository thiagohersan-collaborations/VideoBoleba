#define ANALOG_IN A0
#define THRESH 100
#define ONTIME   555
#define ONDELAY  1000


// state variables
int ledState;
unsigned long lastOn, lastOff;
unsigned long toTurnOn;

void setup() {
  // setup
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);

  // initial state
  ledState = LOW;
  lastOn = millis();
  lastOff = millis();
  toTurnOn = -1;

  // pin stuff
  digitalWrite(13,ledState);
  digitalWrite(12,ledState);
  //analogReference(DEFAULT);    // 5V  
  //analogReference(EXTERNAL);   // 
  analogReference(INTERNAL);    // 1.1V
}

void loop() {
  // read analog in
  int val = analogRead(ANALOG_IN);

  // if off and saw a value and haven't seen other value yet and have been off for 1 second
  //    then set up a time to turn on
  if((ledState == LOW)&&(val > THRESH)&&(toTurnOn == -1)&&((millis()-lastOff) > 1000)){
    toTurnOn = millis()+ONDELAY;
  }
  // if off and have seen a high value and it's time to turn on
  else if((ledState == LOW)&&(toTurnOn != -1)&&(millis() > toTurnOn)){
    ledState = HIGH;
    toTurnOn = -1;
    digitalWrite(13,ledState);
    digitalWrite(12,ledState);
    lastOn = millis();    
  }
  // if on for more than ONTIME milliseconds
  else if((ledState == HIGH)&&((millis()-lastOn) > ONTIME)){
    ledState = LOW;
    digitalWrite(13,ledState);
    digitalWrite(12,ledState);
    lastOff = millis();
  }

  Serial.write( 0xff);
  Serial.write( (val >> 8) & 0xff);
  Serial.write( val & 0xff);
}






