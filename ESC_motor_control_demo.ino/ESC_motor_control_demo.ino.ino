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
  int throttle = analogRead(throttlePin);
  throttle = map(throttle, 0, 1023, 1120, 2000);
  Serial.println(throttle);
  esc.write(throttle);
}
