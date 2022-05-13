unsigned long time;
int button1 = 1;
int button2 = 2;
int button3 = 3;
bool button1_state = false;
bool button2_state = false;
bool button3_state = false;
bool button1_state_prev = false;
bool button2_state_prev = false;
bool button3_state_prev = false;

int state = 1;  // initial state is 1 
int led1 = 12;
int led2 = 11;
int led3 = 10;

void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);   //initialize serial monitor
delay(50);
}

void loop() {
  // put your main code here, to run repeatedly:
  // this loop is the state control HQ 


//time is printed in monitor in milliseconds, "time" variable is declared
Serial.print("Time:"); time = millis();
Serial.print(time); 

//State is printed each loop. 
Serial.print("  State:");
Serial.println(state);

//button states are taken from physical buttons 
button1_state = digitalRead(button1);
button2_state = digitalRead(button2);
button3_state = digitalRead(button3);

//logic for switching between states. Case 0 is the initial state, 
switch(state) {
  case 0:  //standby  (can only go here from state 3, can only go to state 1 from here)
  if (button1_state > button1_state_prev){
    analogWrite(led2,LOW);
    analogWrite(led3,LOW);
    state = 1;
  }
  break;
  
  case 1:    //state1  (can go from here to either 0, 2 or 3)
  if (button2_state > button2_state_prev){
    analogWrite(led1,LOW);
    state = 2;
  }
  if (button3_state > button3_state_prev){
    analogWrite(led1,LOW);
    state = 3; 
  }
  break;

  case 2:   //state2  (can go from here to either 1 or 3)
  if (button1_state > button1_state_prev){
    analogWrite(led2,LOW);
    state = 1;
  }
  if (button3_state > button3_state_prev){
    analogWrite(led2,LOW);
    state = 3; 
  }
  break;

  case 3:   //state3  (can go from here to either 1,2. Can go to state 0 from here by pressing button 3)
  if (button1_state > button1_state_prev){
    analogWrite(led3,LOW);
    state = 1;
  }
  if (button2_state > button2_state_prev){
    analogWrite(led3,LOW);
    state = 2; 
  }
  if (button3_state > button3_state_prev){
    analogWrite(led3,LOW);
    state = 0; 
  }
  break;


}

//assign current button state to previous for comparison with next loop. 
button1_state_prev = button1_state;
button2_state_prev = button2_state;
button3_state_prev = button3_state;

// call each state function based on the state
if (state == 1)   {state1(time);
//Serial.print("state1 ");
}

if (state == 2)   {state2(time);
//Serial.print("state2 ");
}

if (state == 3)   {state3(time);
//Serial.print("state3 ");
}


}

//Function for State 1
void state1(int time)   {

int sec = time / 1000;    //convert from ms to s

if ((sec % 2) == 0) {analogWrite(led1,HIGH);  //If time in seconds is even, light 1 turns on
} 
else{
analogWrite(led1,LOW);    //light is off if time is odd
}
}

//Function for State 2
void state2(int time)   {

int sec = time / 1000;

if (sec % 2 == 0) {analogWrite(led2,HIGH);  //state 2 uses light 2 
} 
else{
analogWrite(led2,LOW);
}
}

//Function for State 3
void state3(int time)   {

int sec = time / 1000;

if (sec % 2 == 0) {analogWrite(led3,HIGH);  //state 3 uses light 3
} 
else{
analogWrite(led3,LOW);
}
}