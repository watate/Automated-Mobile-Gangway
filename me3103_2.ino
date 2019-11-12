//LINEAR ACTUATOR
//Define interrupt pins for Linear Actuator
#define button1 2
#define button2 3

//Linear Actuator Settings
#define motorPin1 4
#define motorPin2 5

//STEPPER MOTOR
// Define interrupt pins for stepper motor
# define button3 18
# define button4 19

//SM Driver 1 settings
#define dirPin1 6
#define stepPin1 7

//SM Driver 2 settings
#define dirPin2 8
#define stepPin2 9

//SM Universal settings
#define stepsPerRevolution 3
#define stepDelay 16000
#define stepDelay2 15000 //This test delay is for stepPin Low, which allows the stepping to change quickly

//Interrupt duration
#define interrupt_duration 200

volatile int mode = 3;

//This will run only one time.
void setup(){
//LINEAR ACTUATOR
  //Set linear actuator interrupt pins as input
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  
  //Set up interrupts
  attachInterrupt(digitalPinToInterrupt(button1), forward, CHANGE);
  attachInterrupt(digitalPinToInterrupt(button2), backward, CHANGE);

  //Set pins as outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);

//STEPPER MOTOR
  // Declare stepper motor pins as output:
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
    
  //Enable interrupt pins as input
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
  
  //Set up interrupt pins as interrupts
  attachInterrupt(digitalPinToInterrupt(button3), clockwise, CHANGE);
  attachInterrupt(digitalPinToInterrupt(button4), anticlockwise, CHANGE);

  //Enable serial monitor
  Serial.begin(9600);
  
}


void loop(){
  /*
   * Mode 1 = LA Forward
   * Mode 2 = LA Backward
   * Mode 3 = LA Stop
   * Mode 4 = SM Clockwise
   * Mode 5 = SM Anticlockwise
    */

   switch(mode){
    case 1:
      analogWrite(motorPin1, 255);
      analogWrite(motorPin2, 0);
      //delay(5000);
      break;
    case 2:
      analogWrite(motorPin1, 0);
      analogWrite(motorPin2, 255);
      //delay(5000);
      break;
    case 3:
      analogWrite(motorPin1, 0);
      analogWrite(motorPin2, 0);
      //delay(5000);
      break;
    case 4:
      // Set the spinning direction clockwise:
      digitalWrite(dirPin1, HIGH);
      digitalWrite(dirPin2, HIGH);
      // Spin the stepper motor 5 revolutions fast:
      for (int i = 0; i < stepsPerRevolution; i++) {
        // These four lines result in 1 step:
        digitalWrite(stepPin1, HIGH);
        digitalWrite(stepPin2, HIGH);
        delayMicroseconds(stepDelay);
        digitalWrite(stepPin1, LOW);
        digitalWrite(stepPin2, LOW);
        delayMicroseconds(stepDelay2);
      }
      break;
    case 5:
      // Set the spinning direction counterclockwise:
      digitalWrite(dirPin1, LOW);
      digitalWrite(dirPin2, LOW);
      //Spin the stepper motor 5 revolutions fast:
      for (int i = 0; i < stepsPerRevolution; i++) {
        // These four lines result in 1 step:
        digitalWrite(stepPin1, HIGH);
        digitalWrite(stepPin2, HIGH);
        delayMicroseconds(stepDelay);
        digitalWrite(stepPin1, LOW);
        digitalWrite(stepPin2, LOW);
        delayMicroseconds(stepDelay2);
      }
      break;
   }
  
}


void forward(){
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 200ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > interrupt_duration)
  {
    delay(350);
    int stateButton = digitalRead(button1);
    //Serial.print(stateButton);
    //Serial.print("\n");
    switch(stateButton){
      case 0:
        mode = 3;
        Serial.print("BUTTON 1 RELEASED");
        Serial.print("\n");
        break;
      case 1:
        mode = 1;
        Serial.print("BUTTON 1 PRESSED");
        Serial.print("\n");
        break;
    }
  }
  last_interrupt_time = interrupt_time;
}

void backward(){
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 200ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > interrupt_duration)
  {
    delay(350);
    int stateButton = digitalRead(button2);
    switch(stateButton){
      case 0:
        mode = 3;
        Serial.print("BUTTON 2 RELEASED");
        Serial.print("\n");
        break;
      case 1:
        mode = 2;
        Serial.print("BUTTON 2 PRESSED");
        Serial.print("\n");
        break;
    }
  }
  last_interrupt_time = interrupt_time;
}



void clockwise(){
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 200ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > interrupt_duration)
  {
    delay(350);
    int stateButton = digitalRead(button3);
    //Serial.print(stateButton);
    //Serial.print("\n");
    switch(stateButton){
      case 0:
        mode = 3;
        Serial.print("BUTTON 3 RELEASED");
        Serial.print("\n");
        break;
      case 1:
        mode = 4;
        Serial.print("BUTTON 3 PRESSED");
        Serial.print("\n");
        break;
    }
  }
  last_interrupt_time = interrupt_time;
}

void anticlockwise(){
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 200ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > interrupt_duration)
  {
    delay(350);
    int stateButton = digitalRead(button4);
    switch(stateButton){
      case 0:
        mode = 3;
        Serial.print("BUTTON 4 RELEASED");
        Serial.print("\n");
        break;
      case 1:
        mode = 5;
        Serial.print("BUTTON 4 PRESSED");
        Serial.print("\n");
        break;
    }
  }
  last_interrupt_time = interrupt_time;
}
