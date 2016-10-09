/*
 * calc_tcp.c
 *
 *  Created on: Oct 9, 2016
 *      Author: root
 */

#include "calculadora.h"



int task_server_tcp(int socket)
{

	int socket_efimero = socket;
	char solucion[SOL_SIZE];
	char mensaje_verificado[MES_LEN];
	char operacion_a_realizar[OP_LEN];

	if ( (socket_efimero < 1) )
			return -1;


	int rec = read(socket_efimero, operacion_a_realizar, sizeof(operacion_a_realizar));

	if (rec <= 0) {
		perror("tcp server read: zero bytes");
		//exit(-1);
		//goto retorno_fallo_read_zero;
		return -1;
	}

	//solucion =
	do_server_logic(&operacion_a_realizar, rec, &mensaje_verificado, &solucion);


	if (write(socket_efimero, solucion, sizeof(solucion)) < 0) {
		perror("tcp server fallo write");
	}

	close(socket_efimero);


}
