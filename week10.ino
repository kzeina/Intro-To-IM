int photoPins[3] = {A0, A1, A2};// first we define a list of integers holding the analog pins
int buttonPin = 2; // digi pin 2 for the buttons
int piezzoPin = 8; //digi pin 8 for the piezzo speaker 

int threshold = 700; //this is the threshold fo rte light/no light intensity that worked wit our light sensors in our environment/lighting

bool prevPhoto[3] = {false, false, false}; //keeping track of whether the light sebsir was interacted with or not false initially 
bool prevButton = false; //initially false
bool buttonState = false;//initially false

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); //for the button pint as an input for the arduino
  pinMode(piezzoPin, OUTPUT); //setting the buzzor pin as output so the arduino sneds the sound signal 
  Serial.begin(9600); // serial monitor for debugging
}

void loop() {
  for (int i = 0; i < 3; i++) { //looping over the 3 sensors to reasd their analog value
    int value = analogRead(photoPins[i]); 
    bool tapped = value < threshold; //comparing the value captured by the sensor and the defined threshold
    if (tapped && !prevPhoto[i]) { //checking for tap in the current state compared to prev
      if (i == 0) tone(piezzoPin, 440, 200); // translates to A0
      if (i == 1) tone(piezzoPin, 523, 200); // translates to A1
      if (i == 2) tone(piezzoPin, 659, 200); // translates to A2
    }
    prevPhoto[i] = tapped; //MAKING SURE TO NOTE it as tapped to have a singular tap rather than looping

    Serial.print(value); //serial print
    Serial.print(",");
  }

  bool pressed = digitalRead(buttonPin) == LOW; //setting the reading of the button to low meaning the button is pressed
  if (pressed && !prevButton) { //when the button is pressed state changes from not pressed(false) to presssed(true)
    buttonState = !buttonState;
    if (buttonState) tone(piezzoPin, 784);// if toggled on play a continuoue G5 tone
    else noTone(piezzoPin); //otherwise stop the buzzer
  }
  prevButton = pressed; 

  Serial.println(pressed ? "1" : "0"); //for monitoring purposes

  delay(50);//short delay 
}
