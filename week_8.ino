//set the variables 
//easier to manage
//pins 
const int trigPin = 9;
const int echoPin = 10;
const int yellowLED = 3;
const int redLED = 4;
//distance
//what's far and what's close
long distance;
const int farThreshold = 20;   
const int closeThreshold = 10; 

void setup() {
  pinMode(trigPin, OUTPUT); //sends pulse
  pinMode(echoPin, INPUT); //recieves it
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  Serial.begin(9600); //so i can use serial monitor to see if everythings working properly
}

//the sensor measures distance by:
//sending an ultrasonic sound wave (inaudible ping).
//waiting for it to bounce back from an object (echo).
//measuring how long it took for that sound to return.
//since sound travels at a known speed, you can calculate the distance using time.
//-trig tells the sensor to start a measurment
long readDistance() {
  //low for clean start
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  //convert to cm
  //sound speed ≈ 343 m/s → 0.034 cm/µs.
  //div 2 cause roundtrip
  return duration * 0.034 / 2; 
}

void loop() {
  distance = readDistance();
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance > closeThreshold && distance <= farThreshold) {
    //when far, light yellow
    digitalWrite(yellowLED, HIGH); 
    digitalWrite(redLED, LOW);
  } else if (distance <= closeThreshold) {
    digitalWrite(yellowLED, LOW);
    //when close, light red
    digitalWrite(redLED, HIGH);    
  } else {
    //too far, both should be off
    digitalWrite(yellowLED, LOW);  
    digitalWrite(redLED, LOW);
  }
  //small delay for stability
  delay(100); 
}
