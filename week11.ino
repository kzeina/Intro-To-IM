void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(A1); // 0–1023
  Serial.println(sensorValue);             // send to p5.js
  delay(50);
}
