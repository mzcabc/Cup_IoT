#include <SPI.h>
#include <Ethernet.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int UltrasoundSensorHeight = 20.0;
int CupHeight = 5;

int countForJson = 0;
int ultrasoundTrigPin = 2;
int ultrasoundEchoPin = 3;
int pumpControlPin = 4;
int lightSensorPin = 5;

int waterHeight = 0;
int drankWaterHeight = 0;
int drankWaterML = 0;
int distanceFromTopCM = 0;
int lightSensorState = 0;
int incomingByte = 0;
int lastWaterHeight = 0;
int lastLightSensorState = 0;
LiquidCrystal_I2C lcd(0x27, 20, 4);

EthernetClient client;
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
EthernetServer server(80);
String htmlStr = "";

void setup() {
  pinMode(ultrasoundTrigPin, OUTPUT_FAST);
  pinMode(ultrasoundEchoPin, INPUT_FAST);
  pinMode(pumpControlPin, OUTPUT);
  pinMode(lightSensorPin, INPUT);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  Serial.begin(9600);
  digitalWrite(pumpControlPin, HIGH);

  Ethernet.begin(mac);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  digitalWrite(ultrasoundTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultrasoundTrigPin, LOW);
  distanceFromTopCM = pulseIn(ultrasoundEchoPin, HIGH) / 58;
  waterHeight = UltrasoundSensorHeight - distanceFromTopCM;
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print(waterHeight);
  lightSensorState = digitalRead(lightSensorPin);
  lcd.setCursor(0, 1);
  lcd.print("Water:");

  if (lightSensorState == 0) {
    digitalWrite(pumpControlPin, HIGH);
    lcd.setCursor(6, 0);
    lcd.print("Picked Up");
    lastWaterHeight = waterHeight;
    lastLightSensorState = 0;
  } else if (lightSensorState == 1) {
    lcd.setCursor(6, 0);
    drankWaterHeight = waterHeight - lastWaterHeight;
    drankWaterML = drankWaterHeight * 36;
    lcd.print("On Desk ");
    if (lastLightSensorState == 0) {
      htmlStr = String("{\"status\":\"ok\",\"results\": [") +
                "{" +
                "\"id\":" + countForJson + "," +
                "\"time\":\"2016 - 04 - 20\", " +
                "\"waterHeight\":" + waterHeight + "," +
                "\"lastWaterHeight\":" + lastWaterHeight + "," +
                "\"drankWaterHeight\":" + drankWaterHeight + "," +
                "\"drankWaterML\":" + drankWaterML +
                "}" +
                "]}";
      /*
            htmlStr = String("countForJson: ") + countForJson + "<br />"
                      "waterHeight: " + waterHeight + "<br />"
                      + "lastWaterHeight: " + lastWaterHeight + "<br />"
                      + "drankWaterHeight: " + drankWaterHeight + "<br />";
      */
      countForJson++;
      /*
            //debug
            Serial.print("waterHeight: ");
            Serial.println(waterHeight);
            Serial.print("lastWaterHeight: ");
            Serial.println(lastWaterHeight);

            Serial.print("drank: ");
            Serial.println(drankWaterHeight);
            Serial.println("////////////////////////////////////////");
      */
    }
    if (waterHeight  > CupHeight) {
      lcd.setCursor(6, 1);
      lcd.print("Full :)");
      digitalWrite(pumpControlPin, HIGH);
    } else if (waterHeight  < CupHeight) {
      delay(1000);
      lcd.setCursor(6, 1);
      lcd.print("Pumping");
      digitalWrite(pumpControlPin, LOW);
      delay(1000);
    }
    lastLightSensorState = 1;
  } else {
    ;
  }


  client = server.available();
  if (client) {
    Serial.println("new client");
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          SendHTML(htmlStr);
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }

}

void SendHTML(String htmlStr) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();
  /*
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<head>");
    client.println("<meta http-equiv=\"refresh\" content=\"5\">");
    client.println("<title>Cup</title>");
    client.println("</head>");
    client.println("<body>");
  */
  client.println(htmlStr);
  /*
    client.println("</body>");
    client.println("</html>");
  */
}
