int pin;
boolean goingUp;

double frameRate = 15.0;
int numberOfColumns = 128;
unsigned long prevTime;
double frequency = frameRate * numberOfColumns;
unsigned long periodUs;

unsigned int delayUs = 160;

int counter;

void setup()
{
  pin = 2;
  goingUp = false;
  
  for(int i = 2; i < 10; i++)
  {
    pinMode(i, OUTPUT);
  }
  
  counter = 0;
  
  periodUs = (1.0/frequency) * 1000000.0;
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
    
    digitalWrite(pin, HIGH);
    delayMicroseconds(0.5 * periodUs);
    digitalWrite(pin, LOW);
    
    switchPin();
//    counter++;
//    if(counter > 12*numberOfColumns)
//    {
//      pin = 2 + ((pin + 1 - 2) % 8);
//      counter = 0;
//    }
  }
  
  
}
