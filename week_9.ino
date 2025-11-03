//define which arduino pins the buttons and leds are connected to
const int buttonPins[3] = {2, 3, 4};  
const int ledPins[3] = {9, 10, 11};   
              

//keeps track of which led is currently on (-1 means none)
int activeLED = -1; 

void setup() {
  //initialize all button and led pins
  for (int i = 0; i < 3; i++) {
    //use internal pull-up resistor (button connects to 5v when pressed)
    //default state is high, pressed = low
    pinMode(buttonPins[i], INPUT_PULLUP);  
    
    //set led pins as outputs
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  //loop through each button to check if it’s pressed
  for (int i = 0; i < 3; i++) {
    //button pressed (low because of input_pullup)
    if (digitalRead(buttonPins[i]) == LOW) {  
      //set this led as the active one
      activeLED = i;                          

      //turn off all other leds
      for (int j = 0; j < 3; j++) {
        if (j != i) analogWrite(ledPins[j], 0);
      }
    }
  }

  //if an led is active, adjust its brightness based on the potentiometer
  if (activeLED != -1) {
    //read analog value from potentiometer (0–1023)
    int sensorValue = analogRead(A0);             

    //control brightness of the active led
    analogWrite(ledPins[activeLED], sensorValue/4);   
  }
}
