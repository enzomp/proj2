#include <Arduino.h>
#include "def.h"

float tempAtual;

void temp_LM35() {

	float vet[100];
	float aux;

	aux = 0;
	for (int i = 0; i < 100; i++) {
		vet[i] = (float(analogRead(LM35)) * 5 / (1023)) / 0.01;
		aux += vet[i];
	}

	aux = (aux / 100);
	tempAtual = aux;

}
