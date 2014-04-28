int counter = 0;

void setup()
{
	Serial.begin(115200);
	Serial.println("Hello!");
	attachInterrupt(0, alert, FALLING);
}

void alert()
{
	Serial.print(counter++);
	Serial.println("LOW!");
}

void loop()
{

}