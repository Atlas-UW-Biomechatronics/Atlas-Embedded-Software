#include <Servo.h>
 
Servo esc;
int throttlePin = 0;
 
void setup()
{
  Serial.begin(18000);  
  esc.attach(9);
}
 
void loop()
{
  int minVal = 900;
  esc.write(minVal);
  delay(7500);
  for (int i = 0; i < 700; i += 20){  
  delay(1000);
  Serial.println(minVal+i);
  esc.write(minVal+i);
  }
}
