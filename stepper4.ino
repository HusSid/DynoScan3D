
// Define Constants
 
// Connections to A4988
const int dirPin = 7;  // Direction
const int stepPin = 3; // Step
const int MS1 = 4;
const int MS2 = 5;
const int MS3 = 6;
 
// Motor steps per rotation
const int STEPS_PER_REV = 3200;

//interrupt pin
const byte interruptPin = 2;

//initial state as off 
volatile byte state = LOW;
 
void setup() {
  
  // Setup the pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);
  
  //sixteenth stepping
  digitalWrite(MS1,HIGH); 
  digitalWrite(MS2,HIGH); 
  digitalWrite(MS3,HIGH); 
  
  // Set motor direction clockwise
  digitalWrite(dirPin,HIGH); 

  //interrupt set up
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), onoff, CHANGE);
  Serial.begin(9600);
}

void loop() {
  start = Serial.read();
  if (start == '1'){
    state = HIGH;
    else{
      state = LOW;
    }
  }
  Serial.println(state);
  if (state == HIGH){
    Serial.println("start");
    // Spin motor one rotation slowly
    for(int x = 0; x < STEPS_PER_REV/4  ; x++) {
      digitalWrite(stepPin,HIGH); 
      delayMicroseconds(20000); 
      digitalWrite(stepPin,LOW); 
      delayMicroseconds(20000); 
    }
    Serial.println(state);
    // Pause for one second
    delay(3000); 
    state = LOW;
  }
  else{
    //Serial.println("nope");
  }
  
}

void onoff(){
  state = 1;
}
