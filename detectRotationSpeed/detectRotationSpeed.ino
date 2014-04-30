int counter = 0;

boolean on = false;

void setup()
{
	for(int i = 3; i < 11; i++)
	{
		pinMode(i, OUTPUT);
	}
	Serial.begin(115200);
	Serial.println("Hello!");
	attachInterrupt(0, alert, FALLING);
}

void alert()
{
	//Serial.print(counter++);
	//Serial.println(" LOW!");
	
	if(on)
	{
		for(int i = 3; i < 11; i++)
		{
			digitalWrite(i, LOW);
		}
		on = false;
	}
	else
	{
		for(int i = 3; i < 11; i++)
		{
			digitalWrite(i, HIGH);
		}
		on = true;
	}
	
}

void loop()
{

}