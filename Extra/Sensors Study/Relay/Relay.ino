
void setup() {
  Serial.begin(9600);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}

void loop() {
  analogWrite(6, 80);
  digitalWrite(7, HIGH);
  Serial.println("7 HIGH");
  delay(2000);
  digitalWrite(7, LOW);
  Serial.println("7 LOW");
  delay(2000);
}
