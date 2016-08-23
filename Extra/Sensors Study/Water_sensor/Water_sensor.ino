/* Flood Sensor

  This sketch will light up the LED on Pin 13, when water (anything conductive) bridges the gap in the sensor.

  created 02/09/09
  by n00b


*/

const int floodSensors = 2;     // the number of the Flood Sensor pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int floodSensorState = 0;         // variable for reading the floodSensors status

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the flood Sensor pin as an input:
  pinMode(floodSensors, INPUT);
}

void loop() {
  // read the state of the flood Sensor value:
  floodSensorState = digitalRead(floodSensors);

  // check if the flood Sensor is wet.
  // if it is, the floodSensorState is HIGH:
  if (floodSensorState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, LOW);
  }
  else {
    // turn LED off:
    digitalWrite(ledPin, HIGH);
  }
}

