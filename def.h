#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

/* TELAS */
#define MAIN	    	 0
#define SETPOINT    	 1
#define GAINH	    	 2
#define GAINF	    	 3
#define MANUAL           4
#define HEAT 	         5
#define FAN		    	 6
#define DRIVER	    	 7

/* PINOS */
#define LM35  	   			A0
#define IN1		   			5
#define IN2		   			6
#define ENABLE	   			7
#define PIN_HEART_BEATING 	0

/* DELAY HEARTBEAT */
#define DELAY_HEART_BEATING 500

/* TEMPERATURA */
#define MAX_SETPOINT 50
#define MIN_SETPOINT 10

/* VARIÁVEIS GLOBAIS */
extern float tempAtual;
extern float setpoint;
extern float gainH;
extern float gainF;
extern bool manualMode;
extern int heatPWM;
extern int fanPWM;
extern int heatState;
extern int fanState;
extern int driverState;
extern int screen;
extern int inh;
extern int inf;
extern int fanManual;
extern int heatManual;

/* FUNÇÕES MAIN */
void heartbeat();

/* FUNÇÕES LCD */
void iniciaLCD();
void menu_inicio();
void menu_setpoint();
void menu_ganhoH();
void menu_ganhoF();
void menu_manual();
void menu_heat();
void menu_vent();
void menu_driver();
void switchTela();

/* BOTÕES */
void botoes();
void debouncer();
void update();
bool p_button();
bool set_button();
bool up_button();
bool down_button();

/* CONTROLADOR */
extern void iniciaControlador();
void controlador();
void heatState_manual_config();
void heatPWM_config();
void heatPWM_read();
void fanState_manual_config();
void fanPWM_config();
void fanPWM_read();
void driverState_config();
void driverRead();
void gainH_config();
void gainF_config();
void manualMode_config();
void start();

/* LM35 */
extern void temp_LM35();

#endif /* DEFINITIONS_H_ */
