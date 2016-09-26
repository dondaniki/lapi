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



int ejecuta_calculo (char * msg_2_compute, char ** sol);
int verifica_mensaje (char * msg_2_check, char ** sol);


#endif /* CALCULADORA_H_ */
