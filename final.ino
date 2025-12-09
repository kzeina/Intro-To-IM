//input from copper tapes
const int glovePin = 7; 
const int ledPin = 8;  

void setup() {
  pinMode(glovePin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  //should read 1 if tapes are touching
  //causing spidey to jump in p5
  //0 if not
  int glove = digitalRead(glovePin) == LOW ? 1 : 0;
  Serial.println(glove);

  //p5 to arduino
  //when spidey jumps, led turns on
  if (Serial.available()) {
    char cmd = Serial.read();
    if (cmd == '1') digitalWrite(ledPin, HIGH); 
    if (cmd == '0') digitalWrite(ledPin, LOW);  
  }

  delay(20);
}
