#include <Servo.h>

const int signal = 9;
const int trig = 4;
const int echo = 5;
Servo servo1;

int lastMillis = 0;
int speed = 0;
boolean on = true;

void setup()
{
  Serial.begin(9600);
  servo1.attach(signal);
  servo1.write(speed);
  
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop()
{
  if(on)
  {
  
  while (Serial.available() > 0) {
    int input = Serial.parseInt();
    if(input >= 0 && input <= 180)
    {
      Serial.print("Speed: ");
      Serial.println(input);
      servo1.write(input);
    }
    else if(input == 999 )
    {
      servo1.write(0);
      delay(1000);
      on = false;
      Serial.println("Exiting");
    }
    else
      Serial.println("Input invalid");
  }
  }
}
