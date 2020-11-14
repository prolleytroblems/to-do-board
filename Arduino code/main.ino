
// constants won't change. They're used here to set pin numbers:

const int ledPin[] = {A3,A2,A1,A0};      // the number of the LED pin
    
const int switchPin[] = {9,10,11,12};   // the number of the tactile switch pin
const int constPin[] = {2,3,4,5};

// variables will change:
int completeState = 1;         // the value that will be considered complete, alternates each day
int allComplete = 0;
int switchState = 0;

void hideLeds(int led1, int led2) {
  // light up all pins but the ones sent to this function 
  for (int pin = 0; pin < 4; pin++){
    if ( (led1!= pin) & (led2!=pin) ){
      digitalWrite(ledPin[pin], HIGH);  
    } else {
      digitalWrite(ledPin[pin], LOW);
    }
  }
}

void cycleLeds(){
  // cycle through leds back and forth 
  for (int pin = 0; pin < 4; pin++) {
    hideLeds(pin, pin-1); 
    delay(100);
  }
  hideLeds(-1, 3);
  delay(100);
  hideLeds(-1, -1);
  delay(100);
  
  for (int pin = 4; pin > 0; pin--) {
    hideLeds(pin, pin-1); 
    delay(100);
  }
  hideLeds(-1, 0);
  delay(100);
  hideLeds(-1, -1);
  delay(100);
}

void flashLeds() {
  for (int pin = 0; pin < 4; pin++){
    digitalWrite(ledPin[pin], LOW);
  }
  delay(500);
  for (int pin = 0; pin < 4; pin++) {
    digitalWrite(ledPin[pin], HIGH);
  }
  delay(500);
}

void complete() {
  delay(500);
  fanfare();
  delay(500);
  cycleLeds();
  delay(250);
  cycleLeds();
  delay(250);
  for (int pin = 3; pin > -1; pin--) {
    digitalWrite(ledPin[pin], LOW);
    delay(100);
  }

  // swap completeState from 1 to 0 or vice-versa
  completeState = ~completeState+2;
}

void updateLeds() {
  // turn each LED on if the corresponding switch is in the completeState value
  allComplete = 1;
  for (int pin = 0; pin < 4; pin++) {
    switchState = digitalRead(switchPin[pin]) * completeState + ( 1-digitalRead(switchPin[pin]) ) * ( 1-completeState );
    digitalWrite(ledPin[pin], switchState);
    allComplete = allComplete * switchState;
    //Serial.println(digitalRead(switchPin[pin]));
    //Serial.println(switchState);

  }

  if (allComplete == 1) {
    complete();
  }
}

void note(int pin, float freq, int duration) {
  tone(pin, freq, duration-60);
  delay(duration);
}

void allOn() {
  for (int pin = 0; pin < 4; pin++) {
    digitalWrite(ledPin[pin], HIGH);
  }
}

void allOff() {
  for (int pin = 0; pin < 4; pin++){
  digitalWrite(ledPin[pin], LOW);
  }
}

void fanfare() {
  float rate = 1.5;
  
  allOff();  
  note(13, 2*261.6, 200/rate);
  note(13, 2*261.6, 200/rate);
  note(13, 2*261.6, 200/rate);

  allOn();
  note(13, 2*261.6, 600/rate);

  allOff();
  note(13, 2*207.7, 600/rate);

  allOn();
  note(13, 2*233.1, 600/rate);

  allOff();
  note(13, 2*261.6, 400/rate);
  note(13, 2*233.1, 200/rate);

  allOn();
  note(13, 2*261.6, 600/rate);
  
}

void setup() {
  // initialize the LED pins as an output and switch pins as input:
  for (int pin = 0; pin < 4; pin++) {
    pinMode(ledPin[pin], OUTPUT);
    pinMode(switchPin[pin], INPUT);
    pinMode(constPin[pin], OUTPUT);
    digitalWrite(constPin[pin], HIGH);
  }
  Serial.begin(9600);
}

void loop() {
  // read the state of the pushbutton value:
  updateLeds();
  // delay(1000);
}
