/*
 * ejecuta_calculo.c
 *
 *  Created on: Sep 25, 2016
 *      Author: root
 */

#include "calculadora.h"

int ejecuta_calculo(char * msg_2_compute, char ** sol) {
	char operador, operando1, operando2;
	int resultado_parcial = 0;
	char solucion[2];

	if (msg_2_compute == NULL)
		return -1;
	if (sol == NULL)
		return -1;
	if (sizeof(sol) < 2)
		return -1;

	operador = msg_2_compute[0];
	operando1 = msg_2_compute[1];
	operando2 = msg_2_compute[2];

	printf("%c\n", operador);
	printf("%d\n", operando1);
	printf("%d\n", operando2);

	switch (operador) {
	case '+':
		resultado_parcial = (operando1) + (operando2);
		printf("%d\n", resultado_parcial);
		break;
	case '-':
		resultado_parcial = (operando1) - (operando2);
		printf("%d\n", resultado_parcial);
		break;
	case '*':
		resultado_parcial = (operando1) * (operando2);
		printf("%d\n", resultado_parcial);
		break;
	case '/':
		resultado_parcial = (operando1) / (operando2);
		printf("%d\n", resultado_parcial);
		break;
	default:
		solucion[0] = 'N';
		solucion[1] = 'O';
		memcpy(sol, solucion, sizeof(solucion));
		return -1;

	}

//presentacion del resultado_parcial
	if (resultado_parcial > 10) {
		solucion[0] = (resultado_parcial / 10) + '0';
		solucion[1] = (resultado_parcial % 10) + '0';
	} else if (resultado_parcial < 0) {
		solucion[0] = '-';
		solucion[1] = '0' + abs(resultado_parcial);
	} else {
		solucion[0] = '0';
		solucion[1] = '0' + resultado_parcial;
	}

	memcpy(sol, solucion, sizeof(solucion));
	return 0;

}
