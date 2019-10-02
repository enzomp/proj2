#include <Arduino.h>
#include "def.h"

float setpoint;
float gainH = 10;
float gainF = 10;
int heatPWM = 0;
int fanPWM = 0;
int inh = 0;
int inf = 0;
int heatState = 0;
int fanState = 0;
int driverState = 0;

void iniciaControlador()
{
	setpoint = 25.0;
	pinMode(IN1, OUTPUT);
	pinMode(IN2, OUTPUT);
	pinMode(ENABLE, OUTPUT);
	digitalWrite(IN1, 0);
	digitalWrite(IN2, 0);
	analogWrite(ENABLE, 0);
}

void controlador()
{
	inh = (setpoint - tempAtual) * gainH;
	if(inh > 70) inh = 70;
	inf = (setpoint + tempAtual) * gainF;
	if(inf > 255) inf = 255;
	if(inf < 56) inf = 56;
}

void start()
{
	if(tempAtual < setpoint && manualMode == false)
	{
		heatState = 1;
		fanState = 0;
		heatPWM_read();
	}
	else if(tempAtual > setpoint && manualMode == false)
	{
		heatState = 0;
		fanState = 1;
		fanPWM_read();
	}
	else if(manualMode == true)
	{
		if (heatManual == 1 && fanManual == 0)
		{
			heatPWM = map(heatPWM, 0, 100, 0, 70);
			analogWrite(IN1, heatPWM);
			analogWrite(IN2, 0);
		}
		else if (fanManual == 1 && heatManual == 0) {
			fanPWM = map(fanPWM, 0, 100, 56, 255);
			analogWrite(IN2, fanPWM);
			analogWrite(IN1, 0);
		}

	}
}


void heatPWM_read()
{
	if (manualMode == false)
	{
		analogWrite(IN1, inh);
		analogWrite(IN2, 0);
	}
	else if (manualMode == true)
	{
		if (heatState == 1 && fanState == 0)
		{
			heatPWM = map(heatPWM, 0, 100, 0, 70);
			analogWrite(IN2, heatPWM);
			analogWrite(IN1, 0);
		}
	}
}

void fanPWM_read()
{
	if (manualMode == false)
	{
		analogWrite(IN2, inf);
		analogWrite(IN1, 0);
	}
	else if (manualMode == true)
	{
		if (fanState == 1 && heatState == 0)
		{
			fanPWM = map(fanPWM, 0, 100, 56, 255);
			analogWrite(IN2, fanPWM);
			analogWrite(IN1, 0);
		}
	}
}

void driverRead()
{
	digitalWrite(ENABLE, driverState);
}
