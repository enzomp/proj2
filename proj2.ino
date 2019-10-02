#include "Arduino.h"
#include "def.h"

void heartbeat()
{
	static unsigned long long int millis_heart_beating;

	if(driverState == 1)
	{
		if(millis()-millis_heart_beating >= DELAY_HEART_BEATING)
		{
			millis_heart_beating = millis();
			digitalWrite(PIN_HEART_BEATING, HIGH);
		}
	}
	else if(driverState == 0) digitalWrite(PIN_HEART_BEATING, HIGH);
}

void setup()
{
	pinMode(PIN_HEART_BEATING, OUTPUT);

	botoes();
	debouncer();
	iniciaControlador();
	iniciaLCD();
}

void loop()
{
	switchTela();
}
