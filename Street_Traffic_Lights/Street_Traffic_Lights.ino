// waitingPeriod variable determines the time that the traffic lights wait to let the pedestrians through.
int waitingPeriod = 30000; // milliseconds

// croasingRoadBuzz variable determines the duty cycle of the buzzer when the pedestrian can cross the road.
int crossingRoadBuzz = 127; // milliseconds

// buzzerWaitingPassedTime variable determines the time between each beep when the pedestrian is waiting to cross.
int buzzerWaitingPassedTime = 25; // milliseconds

// buzzerWaitingBuzz variable determines the duty cycle of the buzzer when the pedestrian is waiting to cross.
int buzzerWaitingBuzz = 40; // milliseconds

// The pedestrian variable is used to know if there is a person wishing to cross the road.
bool pedestrian = false;

// The startTime variable is used to measure how much time has passed.
long startTime;

// buzzerStartTime variable is used to determine when the last time the buzzer was on.
long buzzerStartTime;
// buzzerPassedTime variable is used to determine how much time has passed from the start to the present.
long buzzerPassedTime;
// buzzerPower variable is used to determine if the buzzer is powered on.
bool buzzerPower;

// Declares the pins used for each traffic lights.
const int GREEN1 = 2; // Traffic Light 1 Green.
const int YELLOW1 = 3; // Traffic Light 1 Yellow.
const int RED1 = 4; // Traffic Light 1 Red.
const int BUTTON1 = 5; // Traffic Light 1 Button .
const int BUZZER1 = 6; // Traffic Light 1 Buzzer.

const int GREEN2 = 7; // Traffic Light 2 Green.
const int YELLOW2 = 8; // Traffic Light 2 Yellow.
const int RED2 = 9; // Traffic Light 2 Red.
const int BUTTON2 = 10; // Traffic Light 2 Button .
const int BUZZER2 = 11; // Traffic Light 2 Buzzer.

// setup method is called at the start.
void setup() {
  // Records the start time, this is in milliseconds.
  startTime = millis();

  // Begins the serial monitor at a baud rate of 9600 bits per second.
  Serial.begin(9600);

  // Activate the pins that are used.
  pinMode(GREEN1, OUTPUT);
  pinMode(YELLOW1, OUTPUT);
  pinMode(RED1, OUTPUT);
  pinMode(BUTTON1, INPUT_PULLUP); 
  pinMode(BUZZER1, OUTPUT);
  pinMode(GREEN2, OUTPUT);
  pinMode(YELLOW2, OUTPUT);
  pinMode(RED2, OUTPUT);
  pinMode(BUTTON2, INPUT_PULLUP); 
  pinMode(BUZZER2, OUTPUT);

  // Initiates the traffic lights on green.
  green();

  // Activate the buzzers to be off.
  digitalWrite(BUZZER1, LOW); 
  digitalWrite(BUZZER2, LOW); 

}

// The stop function makes the traffics lights go from green to red.
void stop(){
  // Stops the waiting pedestrian buzzing noise.
  analogWrite(BUZZER1, 0);
  analogWrite(BUZZER2, 0);
  yellow();
  delay(1000);
  red();
  analogWrite(BUZZER1, crossingRoadBuzz); 
  analogWrite(BUZZER2, crossingRoadBuzz); 
  delay(5000);
  analogWrite(BUZZER1, 0); 
  analogWrite(BUZZER2, 0); 
  // Resets the pedestrian variable.
  pedestrian = false;
  green();
  
}

// Turns the traffic lights green.
void green(){
  digitalWrite(GREEN1, HIGH); 
  digitalWrite(YELLOW1, LOW); 
  digitalWrite(RED1, LOW); 
  digitalWrite(GREEN2, HIGH); 
  digitalWrite(YELLOW2, LOW); 
  digitalWrite(RED2, LOW); 
  
}

// Turns the traffic lights yellow.
void yellow(){
  digitalWrite(GREEN1, LOW); 
  digitalWrite(YELLOW1, HIGH); 
  digitalWrite(RED1, LOW); 
  digitalWrite(GREEN2, LOW); 
  digitalWrite(YELLOW2, HIGH); 
  digitalWrite(RED2, LOW); 
}

// Turns the traffic lights red.
void red(){
  digitalWrite(GREEN1, LOW); 
  digitalWrite(YELLOW1, LOW); 
  digitalWrite(RED1, HIGH);
  digitalWrite(GREEN2, LOW); 
  digitalWrite(YELLOW2, LOW); 
  digitalWrite(RED2, HIGH); 
}

void loop() {
  long currentTime = millis();
  long passedTime = currentTime - startTime;
  
  if ((passedTime >= waitingPeriod)){
    if (pedestrian){
    stop();
    
    }
    
    startTime = millis();
    
  }
  
  if (pedestrian){
    buzzerPassedTime = currentTime - buzzerStartTime;
    
    if (buzzerPassedTime >= buzzerWaitingPassedTime){
      
    if (buzzerPower){
      analogWrite(BUZZER1, buzzerWaitingBuzz);
      analogWrite(BUZZER2, buzzerWaitingBuzz);
      buzzerPower = false;
      
    } else{
      analogWrite(BUZZER1, 0);
      analogWrite(BUZZER2, 0);
      buzzerPower = true;
      
    }
    
    buzzerStartTime = millis();
    
    }
    
  }
   
  if (((digitalRead(BUTTON1) == LOW) | (digitalRead(BUTTON2) == LOW)) & (!pedestrian)){
    pedestrian = true;
    buzzerStartTime = millis();
    buzzerPower = true;
    Serial.println("Button Pressed");
    
  }
  
}
