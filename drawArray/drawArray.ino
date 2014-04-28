/*  drawArray.ino
*   
*   Display an image as an array
*
*/
#include <cmath>
#define PI 3.14159265
#define INPUT_ARRAY_SIZE 1024

double frameRate = 20.0;
int numberOfColumns = 128;
int numberOfRows = 8;
unsigned long prevTime;
double columnFrequency = frameRate * numberOfColumns;
unsigned long columnPeriodUs = (1.0/columnFrequency) * 1000000.0;

int pinValues[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int currentColumn = 0;

boolean inputArray[INPUT_ARRAY_SIZE] = {1, 1, 1, 1, 1, 1, 1, 1,
                                        0, 1, 0, 0, 0, 0, 0, 0, 
                                        0, 0, 1, 0, 0, 0, 0, 0, 
                                        0, 0, 0, 1, 1, 0, 0, 0, 
                                        0, 0, 0, 0, 0, 1, 0, 0, 
                                        0, 0, 0, 0, 0, 0, 1, 0, 
                                        1, 1, 1, 1, 1, 1, 1, 1,
                                        0, 0, 0, 0, 0, 0, 0, 0, 

                                        0, 0, 0, 0, 0, 0, 0, 0, 
                                        0, 0, 1, 0, 0, 1, 0, 0, 
                                        0, 1, 0, 1, 1, 0, 1, 0, 
                                        0, 1, 0, 1, 1, 0, 1, 0, 
                                        1, 1, 1, 1, 1, 1, 1, 1,
                                        0, 1, 0, 0, 0, 0, 1, 0, 
                                        0, 0, 0, 0, 0, 0, 0, 0, 
                                        0, 0, 0, 0, 0, 0, 0, 0, 

                                        0, 1, 1, 0, 0, 0, 1, 0, 
                                        1, 0, 1, 0, 0, 0, 0, 1, 
                                        1, 0, 0, 1, 0, 0, 0, 1, 
                                        1, 0, 0, 1, 1, 0, 0, 1, 
                                        1, 0, 0, 0, 1, 0, 0, 1, 
                                        1, 0, 0, 0, 0, 1, 0, 1, 
                                        0, 1, 0, 0, 0, 1, 1, 0
                                        };


void initializeSinWave()
{
  inputArray[1023] = true;
  int cycles = 8;
  int period = numberOfColumns / cycles;
  
  for(int i = 0; i < numberOfColumns; i++)
  {
    int highPin = 4 + (int)(3.5 * sin(((double)(i % period)) / period * 2*PI));
    for(int j = 0; j < numberOfRows; j++)
    {
      if(j == highPin)
        inputArray[i * numberOfRows + j] = true;
      else
        inputArray[i * numberOfRows + j] = false;
    }
  }

/*
  for(int i = 0; i < 1024; i++)
  {
    if((i % numberOfRows) == 7)
      Serial.println(inputArray[i]);
    else
    {
      Serial.print(inputArray[i]);
      Serial.print(' ');
    }
  }

  */
}

void updatePinValues()
{
  for(int i = 0; i < 8; i++)
  {
    pinValues[i] = inputArray[currentColumn * 8 + i];
  }

  currentColumn = (currentColumn + 1) % numberOfColumns;
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Hello!");

  for(int i = 2; i < 10; i++)
  {
    pinMode(i, OUTPUT);
  }

  prevTime = micros();

  //initializeSinWave();

  Serial.println("Setup done!");
}

void loop()
{
  unsigned long time = micros();
  if(time - prevTime >= columnPeriodUs)
  {
    prevTime = prevTime + columnPeriodUs;
    
    for(int i = 0; i < 8; i++)
    {
      digitalWrite(i + 2, pinValues[i]);
    }

    updatePinValues();

    delayMicroseconds(0.3 * columnPeriodUs);

    for(int i = 0; i < 8; i++)
    {
      digitalWrite(i + 2, LOW);
    }
  }
}
