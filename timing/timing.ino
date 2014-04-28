/*  timing.ino
*   
*   Used to sync rotation speed and LED frequency
*
*/

int pin;
boolean goingUp;

double frameRate = 15.0;
int numberOfColumns = 128;
int numberOfRows = 8;
unsigned long prevTime;
double frequency = frameRate * numberOfColumns;
unsigned long periodUs = (1.0/frequency) * 1000000.0;

void setup()
{
  pin = 2;
  goingUp = false;
  
  for(int i = 2; i < 10; i++)
  {
    pinMode(i, OUTPUT);
  }

  prevTime = micros();
}

void switchPin()
{
  if(goingUp)
  {
    if((--pin) < 2)
    {
      pin = 3;
      goingUp = false;
    }
  }
  else
  {
    if((++pin) > 9)
    {
      pin = 8;
      goingUp = true;
    }
  }
}

void loop()
{
  unsigned long time = micros();
  if(time - prevTime > periodUs)
  {
    prevTime = prevTime + periodUs;
    
    digitalWrite(pin, 1);
    delayMicroseconds(0.5 * periodUs);
    digitalWrite(pin, 0);
    
    switchPin();
  }
  
  
}
