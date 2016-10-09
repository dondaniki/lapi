/*
 * server_logic.c
 *
 *  Created on: Sep 25, 2016
 *      Author: root
 */

#include "calculadora.h"

void do_server_logic(char* operacion_a_realizar, int rec,
		char* mensaje_verificado, char* solucion) {

	operacion_a_realizar[rec] = '\0';
	printf("recibido server:%s:\n", operacion_a_realizar);

	if (verifica_mensaje(operacion_a_realizar, mensaje_verificado) == 0) {
		ejecuta_calculo(mensaje_verificado, solucion);
	} else {
		solucion[0] = 'N';
		solucion[1] = 'O';
	}
	//return solucion;
}
