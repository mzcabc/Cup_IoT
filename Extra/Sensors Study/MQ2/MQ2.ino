#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int gasPin = A0; //GAS sensor output pin to Arduino analog A0 pin
int gasStatus = 0;
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup()
{
  pinMode(2, OUTPUT);
  //Serial.begin(9600); //Initialize serial port - 9600 bps
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gas:");
}

void loop()
{
  gasStatus = analogRead(gasPin);
  lcd.setCursor(4, 0);
  lcd.print(gasStatus);
  if (gasStatus > 350) {
    digitalWrite(2, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("On FIRE!!!");
  } else {
    digitalWrite(2, LOW);
     lcd.setCursor(0, 1);
     lcd.print("                              ");
  }
  delay(250);
}

