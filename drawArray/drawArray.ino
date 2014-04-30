/*  drawArray.ino
*   
*   Display an image as an array
*
*/
#include <cmath>
#define PI 3.14159265
#define NUMBER_OF_COLUMNS 140
#define NUMBER_OF_ROWS 8
#define INITIAL_FRAME_RATE 20.0

unsigned long prevTime;
unsigned long time;
double columnFrequency = INITIAL_FRAME_RATE * NUMBER_OF_COLUMNS;
volatile unsigned long columnPeriodUs = (1.0/columnFrequency) * 1000000.0;

int pinValues[8] = {0, 0, 0, 0, 0, 0, 0, 0};
volatile int currentColumn = 0;
volatile boolean justHadInterrupt = false;
volatile unsigned long prevInterruptTime;

boolean inputArray[NUMBER_OF_COLUMNS * NUMBER_OF_ROWS] = {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,1,1,0,1,1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,0,1,1,1,1,0,0,0,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void setup()
{
  Serial.begin(115200);
  Serial.println("Hello!");

  attachInterrupt(0, fullRotationInterrupt, FALLING);
  for(int i = 3; i < 11; i++)
  {
    pinMode(i, OUTPUT);
  }

  prevTime = micros();
  prevInterruptTime = micros();
  time = micros();
  //initializeSinWave();

  Serial.println("Setup done!");
}

void loop()
{
  

  if(justHadInterrupt)
  {
      currentColumn = 0;
      justHadInterrupt = false;
      time = micros();
      goto startLoop;
  }

  time = micros();
  if(time - prevTime >= columnPeriodUs)
  {
    startLoop:
    prevTime = time;
    
    for(int i = 0; i < 8; i++)
    {
      digitalWrite(10 - ((8 - i) % 8), inputArray[currentColumn * 8 + i]);
    }

    currentColumn = (currentColumn + 1) % NUMBER_OF_COLUMNS;


    /*
    delayMicroseconds(0.5 * columnPeriodUs);

    for(int i = 0; i < 8; i++)
    {
      digitalWrite(10 - ((8 - i) % 8), LOW);
    }
    */
  }
}

void initializeSinWave()
{
  inputArray[1023] = true;
  int cycles = 8;
  int period = NUMBER_OF_COLUMNS / cycles;
  
  for(int i = 0; i < NUMBER_OF_COLUMNS; i++)
  {
    int highPin = 4 + (int)(3.5 * sin(((double)(i % period)) / period * 2*PI));
    for(int j = 0; j < NUMBER_OF_ROWS; j++)
    {
      if(j == highPin)
        inputArray[i * NUMBER_OF_ROWS + j] = true;
      else
        inputArray[i * NUMBER_OF_ROWS + j] = false;
    }
  }
}

void fullRotationInterrupt()
{
  unsigned long time = micros();
  columnPeriodUs = (unsigned long)((double)(time - prevInterruptTime))/NUMBER_OF_COLUMNS;

  justHadInterrupt = true;
  prevInterruptTime = time;
}
