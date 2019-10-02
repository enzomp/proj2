#include <Arduino.h>
#include "def.h"

int heatManual, fanManual;

void heatState_manual_config()
 {
	update();
	if (p_button())
	{
		if(heatManual == 1) 
			heatManual = 0;
		else
		{
			heatManual = 1;
			fanManual = 0;
			fanState = 0;
			heatState = 0;
		}
	}
}

void heatPWM_config()
{
	update();

	if (up_button())
	{
		if(heatPWM < 100)
			heatPWM += 5;
	}

	if (down_button())
	{
		if(heatPWM > 0)
			heatPWM -= 5;
	}
}

void fanState_manual_config()
{
	update();

	if (p_button())
	{
		if(fanManual == 1) 
			fanManual = 0;
		else
		{
			fanManual = 1;
			heatManual = 0;
			fanState = 0;
			heatState = 0;
		}
	}
}


void fanPWM_config()
{
	update();

	if (up_button()) {
		if(fanPWM < 100)
			fanPWM += 5;
	}

	if (down_button()) {
		if(fanPWM > 0)
			fanPWM -= 5;
	}
}

void driverState_config()
{
	update();

	if (up_button())
		driverState = 1;

	if (down_button())
		driverState = 0;
}

void gainH_config()
{
	update();

	if (up_button())
		gainH += 1;

	if (down_button())
	{
		gainH -= 1;
		if(gainH < 0) gainH = 0;
	}
}

void gainF_config()
{
	update();

	if (up_button())
		gainF += 1;

	if (down_button())
	{
		gainF -= 1;
		if(gainF < 0) gainF = 0;
	}
}

void manualMode_config()
{
	update();

	if (up_button())
		manualMode = true;

	if (down_button())
		manualMode = false;
}

