/*
 * calculadora.h
 *
 *  Created on: Sep 25, 2016
 *      Author: root
 */

#ifndef CALCULADORA_H_
#define CALCULADORA_H_

#define _POSIX_C_SOURCE 2


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#define SOL_SIZE  2
#define MES_LEN 3
#define OP_LEN 4
#define MAX_HIJOS 150


int ejecuta_calculo (char * msg_2_compute, char * sol);
int verifica_mensaje (char * msg_2_check, char * sol);
int task_server_tcp(int socket);
int task_server_udp( int socket);
void do_server_logic(char operacion_a_realizar[OP_LEN], int rec,
		char mensaje_verificado[MES_LEN], char solucion[SOL_SIZE]);

#endif /* CALCULADORA_H_ */
