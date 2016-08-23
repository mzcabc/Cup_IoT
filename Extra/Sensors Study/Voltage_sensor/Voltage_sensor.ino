#include <Wire.h>
int val11;
float val2;


void setup()
{
  Serial.begin(9600);
  Serial.println("Emartee.Com");

  Serial.println("Voltage: ");
  Serial.print("V");
}
void loop()
{
      float temp;
      val11=analogRead(1);
      temp=val11/4.092;
      val2=(temp/10);
      Serial.println(val2);

     
   delay(1000);
}
