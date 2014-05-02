#include <Servo.h>

const int motor = 6;
const int led = 2;
Servo servo1;

int speed = 0;

void setup()
{
  servo1.attach(motor);
  servo1.write(speed);

  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);

  servo1.write(20);
  delay(1000);
  servo1.write(37);
}

void loop()
{

}
