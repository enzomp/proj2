#include "Arduino.h"
#include "def.h"
#include <LiquidCrystal.h>
#include <Bounce2.h>

LiquidCrystal lcd(12, 11, 4, 3, 2, 1);

int screen = MAIN;
bool manualMode = false;

void iniciaLCD() {
	lcd.begin(16, 2);
}

void menu_inicio()
{
	lcd.clear();

	while (screen == MAIN)
	{
		update();
		heartbeat();

		lcd.setCursor(0, 0);
		lcd.print("SP: ");
		delay(100);
		lcd.print(setpoint, 1);

		temp_LM35();

		lcd.setCursor(0, 1);
		lcd.print("PV: ");
		lcd.print(tempAtual, 1);

		driverRead();
		controlador();
		start();

		if (driverState == 0)
		{
			lcd.setCursor(10, 0);
			lcd.print("Driver");
			lcd.setCursor(12, 1);
			lcd.print("OFF");
		}
		else if (driverState == 1 && heatState == 0 && fanState == 0) {
			lcd.setCursor(10, 0);
			lcd.print("Driver");
			lcd.setCursor(12, 1);
			lcd.print("ON ");
		}

		else if (driverState == 1 && heatState == 1 && fanState == 0)
		{
			lcd.setCursor(12, 0);
			lcd.print("Heat");
			lcd.setCursor(12, 1);
			lcd.print("ON ");
		}
		else if (driverState == 1 && fanState == 1 && heatState == 0)
		{
			lcd.setCursor(12, 0);
			lcd.print("Fan ");
			lcd.setCursor(12, 1);
			lcd.print("ON ");
		}
		else if (manualMode == true && heatManual == 1 && fanState == 0)
		{ 
			lcd.setCursor(12, 0);
			lcd.print("  Heat");
			lcd.setCursor(12, 1);
			lcd.print("ON ");
		} 
		else if (manualMode == true && fanManual == 1 && heatState == 0)
		{
			lcd.setCursor(12, 0);
			lcd.print("  Fan ");
			lcd.setCursor(12, 1);
			lcd.print("ON ");
		}
		

		if (p_button())
			screen = SETPOINT;
	}
}


void menu_setpoint()
{
	lcd.clear();

	int config_mode = 0;

	while (screen == SETPOINT)
	{
		update();
		heartbeat();

		lcd.setCursor(0, 0);
		lcd.print("New Set Point");
		lcd.setCursor(0, 1);
		lcd.print("SP: ");
		lcd.print(setpoint, 1);

		if (set_button())
		{
			config_mode = 1;

			lcd.setCursor(8, 1);
			lcd.print("<");

			while (config_mode == 1)
			{
				update();

				if (up_button())
					setpoint += 1;

				if (down_button())
					setpoint -= 1;

				lcd.setCursor(0, 1);
				lcd.print("SP: ");
				lcd.print(setpoint, 1);

				if (set_button()) {
					lcd.setCursor(8, 1);
					lcd.print(" ");
					config_mode = 0;
				}
			}

		}

		if (p_button())
			screen = GAINH;
		}
}

void menu_ganhoH()
{

	int config_mode = 0;
	lcd.clear();

	while (screen == GAINH)
	{
		update();
		heartbeat();

		lcd.setCursor(0, 0);
		lcd.print("New Prop. Gain H");
		lcd.setCursor(0, 1);
		lcd.print("Kp: ");
		lcd.print(gainH, 1);

		if (set_button()) {
			config_mode = 1;

			while (config_mode == 1)
			{
				gainH_config();

				lcd.setCursor(8, 1);
				lcd.print("<");
				lcd.setCursor(4, 1);
				lcd.print(gainH, 1);


				if (set_button()) {
					lcd.setCursor(8, 1);
					lcd.print(" ");
					config_mode = 0;
				}
			}
		}

		if (p_button())
			screen = GAINF;

	}
}

void menu_ganhoF()
{
	lcd.clear();
	int config_mode = 0;

	while (screen == GAINF)
	{
		update();
		heartbeat();

		lcd.setCursor(0, 0);
		lcd.print("New Prop. Gain F");
		lcd.setCursor(0, 1);
		lcd.print("Kp: ");
		lcd.print(gainF, 1);

		if (set_button())
		{
			config_mode = 1;

			while (config_mode == 1)
			{
				gainF_config();

				lcd.setCursor(8, 1);
				lcd.print("<");
				lcd.setCursor(4, 1);
				lcd.print(gainF, 1);


				if (set_button()) {
					lcd.setCursor(8, 1);
					lcd.print(" ");
					config_mode = 0;
				}
			}
		}

		if (p_button())
			screen = MANUAL;

	}
}

void menu_manual()
{
	lcd.clear();
	int config_mode = 0;

	while (screen == MANUAL)
	{
		update();
		heartbeat();

		lcd.setCursor(2, 0);
		lcd.print("Manual Mode");
		if (manualMode == true)
		{
			lcd.setCursor(7, 1);
			lcd.print("ON ");
		}
		else if (manualMode == 0)
		{
			lcd.setCursor(7, 1);
			lcd.print("OFF");
		}

		if (set_button())
		{
			config_mode = 1;

			lcd.setCursor(10, 1);
			lcd.print("<");

			while (config_mode == 1)
			{
				manualMode_config();

				if (manualMode == 1) {
					lcd.setCursor(7, 1);
					lcd.print("ON ");
				}
				else if (manualMode == 0) {
					lcd.setCursor(7, 1);
					lcd.print("OFF");
				}

				if (set_button())
				{
					lcd.setCursor(10, 1);
					lcd.print(" ");
					config_mode = 0;
				}
			}

		}

		if (manualMode == true)
		{
			if (p_button())
				screen = HEAT;
		}
		else if (manualMode == false)
		{
			if (p_button())
				screen = DRIVER;
		}
	}

}

void menu_heat()
{
	lcd.clear();
	int config_mode = 0;

	while (screen == HEAT)
	{
		update();
		heartbeat();

		lcd.setCursor(2, 0);
		lcd.print("Manual Mode");
		lcd.setCursor(0, 1);
		lcd.print("Heat: ");
		if (heatState == 1 || heatManual == 1)
		{
			lcd.setCursor(6, 1);
			lcd.print("ON ");
			lcd.setCursor(11, 1);
			lcd.print(heatPWM);

			if (heatPWM == 100)
			{
				lcd.setCursor(14, 1);
				lcd.print("%");
			}
			else if (heatPWM >= 10)
			{
				lcd.setCursor(13, 1);
				lcd.print("% ");
			}
			else if (heatPWM < 10)
			{
				lcd.setCursor(12, 1);
				lcd.print("%  ");
			}

			digitalWrite(ENABLE, heatState);
		}
		else if (heatState == 0 || heatManual == 0)
		{
			lcd.setCursor(6, 1);
			lcd.print("OFF");
			lcd.setCursor(11, 1);
			lcd.print("    ");
			if(driverState == 0) digitalWrite(ENABLE, driverState);
			else digitalWrite(ENABLE, driverState);
		}

		if (set_button())
		{
			config_mode = 1;

			lcd.setCursor(9, 1);
			lcd.print("<");

			while (config_mode == 1)
			{
				heatState_manual_config();

				if (heatState == 1 || heatManual == 1)
				{
					lcd.setCursor(6, 1);
					lcd.print("ON ");
				}

				else if (heatState == 0 || heatManual == 0) {
					lcd.setCursor(6, 1);
					lcd.print("OFF");
					lcd.setCursor(11, 1);
					lcd.print("    ");
				}

				if (set_button())
				{

					if (heatState == 1 || heatManual == 1)
					{
						config_mode = 2;

						while (config_mode == 2)
						{

							heatPWM_config();

							lcd.setCursor(9, 1);
							lcd.print(">");
							lcd.setCursor(11, 1);
							lcd.print(heatPWM);
							if (heatPWM == 100)
							{
								lcd.setCursor(14, 1);
								lcd.print("%");
							}
							else if (heatPWM >= 10)
							{
								lcd.setCursor(13, 1);
								lcd.print("% ");
							}
							else if (heatPWM < 10)
							{
								lcd.setCursor(12, 1);
								lcd.print("%  ");
							}

							if (set_button())
							{
								config_mode = 0;
								lcd.setCursor(9, 1);
								lcd.print(" ");
							}
						}
					}
					if (heatState == 0 || heatManual == 0)
					{
						config_mode = 0;
						lcd.setCursor(9, 1);
						lcd.print(" ");
					}
				}
			}
		}

		if (p_button())
			screen = FAN;
	}
}

void menu_vent()
{
	lcd.clear();
	int config_mode = 0;

	while (screen == FAN)
	{
		update();
		heartbeat();

		lcd.setCursor(2, 0);
		lcd.print("Manual Mode");
		lcd.setCursor(0, 1);
		lcd.print("Fan: ");
		if (fanState == 1 || fanManual == 1)
		{
			lcd.setCursor(5, 1);
			lcd.print("ON ");
			lcd.setCursor(10, 1);
			lcd.print(fanPWM);
			lcd.setCursor(13, 1);
			if (fanPWM == 100)
			{
				lcd.setCursor(13, 1);
				lcd.print("%");
			}
			else if (fanPWM >= 10)
			{
				lcd.setCursor(12, 1);
				lcd.print("% ");
			}
			else if (fanPWM < 10)
			{
				lcd.setCursor(11, 1);
				lcd.print("%  ");
			}

			digitalWrite(ENABLE, fanState);
		}
		else if (fanState == 0 || fanManual == 0)
		{
			lcd.setCursor(5, 1);
			lcd.print("OFF");
			lcd.setCursor(10, 1);
			lcd.print("    ");
			if(driverState == 0) digitalWrite(ENABLE, driverState);
			else digitalWrite(ENABLE, driverState);
		}

		if (set_button())
		{
			config_mode = 1;

			lcd.setCursor(8, 1);
			lcd.print("<");

			while (config_mode == 1)
			{
				fanState_manual_config();

				if (fanState == 1 || fanManual == 1)
				{
					lcd.setCursor(5, 1);
					lcd.print("ON ");
				}
				else if (fanState == 0 || fanManual == 0)
				{
					lcd.setCursor(5, 1);
					lcd.print("OFF");
					lcd.setCursor(10, 1);
					lcd.print("    ");
				}

				if (set_button())
				{

					if (fanState == 1 || fanManual == 1)
					{
						config_mode = 2;

						while (config_mode == 2)
						{
							fanPWM_config();
							lcd.setCursor(8, 1);
							lcd.print(">");
							lcd.setCursor(10, 1);
							lcd.print(fanPWM);
							if (fanPWM == 100)
							{
								lcd.setCursor(13, 1);
								lcd.print("%");
							}
							else if (fanPWM >= 10)
							{
								lcd.setCursor(12, 1);
								lcd.print("% ");
							}
							else if (fanPWM < 10)
							{
								lcd.setCursor(11, 1);
								lcd.print("%  ");
							}

							if (set_button())
							{
								config_mode = 0;
								lcd.setCursor(8, 1);
								lcd.print(" ");
							}
						}
					}
					if (fanState == 0 || fanManual == 0)
					{
						config_mode = 0;
						lcd.setCursor(8, 1);
						lcd.print(" ");
					}
				}
			}
		}

		if (p_button())
			screen = DRIVER;
	}
}

void menu_driver()
{
	int config_mode = 0;
	lcd.clear();

	while (screen == DRIVER)
	{
		update();
		heartbeat();

		lcd.setCursor(2, 0);
		lcd.print("Driver Status");
		if (driverState == 1)
		{
			lcd.setCursor(4, 1);
			lcd.print("Enabled ");
		}
		else if (driverState == 0)
		{
			lcd.setCursor(4, 1);
			lcd.print("Disabled");
		}

		if (set_button())
		{
			config_mode = 1;

			while (config_mode == 1)
			{
				driverState_config();

				lcd.setCursor(12, 1);
				lcd.print("<");
				if (driverState == 1)
				{
					lcd.setCursor(4, 1);
					lcd.print("Enabled ");
				}
				else if (driverState == 0)
				{
					lcd.setCursor(4, 1);
					lcd.print("Disabled");
				}

				if (set_button())
				{
					lcd.setCursor(12, 1);
					lcd.print(" ");
					driverRead();
					config_mode = 0;
				}
			}
		}

		if (p_button())
			screen = MAIN;
	}
}

void switchTela()
{
	switch (screen)
	{
	case MAIN:
		menu_inicio();
		break;

	case SETPOINT:
		menu_setpoint();
		break;

	case GAINH:
		menu_ganhoH();
		break;

	case GAINF:
		menu_ganhoF();
		break;

	case MANUAL:
		menu_manual();
		break;

	case HEAT:
		menu_heat();
		break;

	case FAN:
		menu_vent();
		break;

	case DRIVER:
		menu_driver();
		break;
	}

}

