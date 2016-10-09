/*
 * task_server_udp.c
 *
 *  Created on: Oct 9, 2016
 *      Author: root
 */

#include "calculadora.h"


int task_server_udp(int socket )
{

	int  sock_srv = socket;
	char solucion[SOL_SIZE];
	char mensaje_verificado[MES_LEN];
	char operacion_a_realizar[OP_LEN];

	struct sockaddr_in client_addr;

	if ( (sock_srv < 1) )
			return -1;


	bzero (&client_addr,sizeof(client_addr));
	int tam= sizeof (client_addr);

	int rec = recvfrom(sock_srv, operacion_a_realizar, sizeof(operacion_a_realizar), 0, &client_addr, &tam);


	if (rec <= 0) {
		perror("udp server read: zero bytes");
		//exit(-1);
		//goto retorno_fallo_read_zero;
		return -1;
	}


	//solucion =
			do_server_logic(&operacion_a_realizar, rec, &mensaje_verificado, &solucion);

	sendto(sock_srv, solucion, sizeof(solucion), 0, &client_addr, tam);


		return 0;

}
