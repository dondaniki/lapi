#include "calculadora.h"

struct sockaddr_in dirMia;
struct sockaddr_in dirCli;
//char mensajeRec[200];

char operacion_a_realizar[4];
char mensaje_verificado[3];
char solucion[2];

//char operador='0';
//int operando1=0;
//int operando2=0;

//int resultado_parcial=0;

int rec;
int s;

main(int argc, char *argv[]) {
	int udp_flag = 0;
	int tcp_flag = 0;
	int multi_flag = 0;
	int port_number = 7777;
	char *pvalue = NULL;
	int index;
	int c;

	if (argc == 1) {

		printf("Usage calculadora_IP_server [-u|-t] [ -p port ]\n");

		exit(1);
	}

	opterr = 0;
	while ((c = getopt(argc, argv, "tup:")) != -1)
		switch (c) {
		case 't':
			tcp_flag = 1;
			break;
		case 'u':
			udp_flag = 1;
			break;
		case 'p':
			pvalue = optarg;
			break;
		default:
			printf("Usage calculadora_IP_server [-u|-t] [ -p port ]\n");

			exit(1);
			;
		}

	// if ( isdigit(atoi(pvalue)))

	if (pvalue != NULL) {

		int length = strlen(pvalue);
		for (int i = 0; i < length; i++)
			if (!isdigit(pvalue[i])) {
				printf("Entered port is not a number\n");
				exit(1);
			}

		port_number = atoi(pvalue);

		if (!((port_number > 1024) && (port_number < 65535))) {
			printf("puerto fuera de rango\n");
			exit(1);
		}
	}

	if ((tcp_flag == udp_flag) && (udp_flag == 1)) {
		printf("Especifique UDP o TCP \n");
		exit(1);
	}
	if ((tcp_flag == 0) && (udp_flag == 0)) {
		//el modo por defecto tcp
		tcp_flag = 1;
	}

	printf("udp_flag = %d, tcp_flag = %d, port_number = %s\n", udp_flag,
			tcp_flag, pvalue);

	printf("udp_flag = %d, tcp_flag = %d\n", udp_flag, tcp_flag);
	printf("port_number = %d\n", port_number);
	////if (pcalc != NULL ) printf ("operacion = %s\n", pcalc);
	//if (pserv != NULL ) printf ("ip = %s\n", pserv);

	// return 0;

	if (tcp_flag) {

		s = socket(AF_INET, SOCK_STREAM, 0);
		;
	} else {
		//s = Udp_server(NULL,pvalue,NULL);
		s = socket(AF_INET, SOCK_DGRAM, 0);

	}

	dirMia.sin_family = AF_INET;
	/* dirMia.sin_addr.s_addr= inet_addr ("127.0.0.1"); */
	dirMia.sin_addr.s_addr = INADDR_ANY;
	dirMia.sin_port = htons(port_number); /* servidor de echo */

	//a sustituir por funcion wrapper
	bind(s, &dirMia, sizeof(dirMia));

	if (tcp_flag) {
		listen(s, 2);
	}

	while (1) {
		bzero(&dirCli, sizeof(dirCli));
		int tam = sizeof(dirCli);
		int sconn;

		if (tcp_flag) {
			sconn = accept(s, &dirCli, &tam);

			rec = read(sconn, operacion_a_realizar,
					sizeof(operacion_a_realizar));
//	  while (rec != 0){
////	  }

			if (rec <= 0) {
				perror("tcp server read: zero bytes");
				exit(-1);
			}

			// while ( n>0 ) {
			//write (sconn,operacion_a_realizar,n);
			//n= read (sconn,operacion_a_realizar,sizeof(operacion_a_realizar));
			//}
			//close (sconn);
		} else {
			rec = recvfrom(s, operacion_a_realizar,
					sizeof(operacion_a_realizar), 0, &dirCli, &tam);

		}

		operacion_a_realizar[rec] = '\0';
		printf("recibido server:%s:\n", operacion_a_realizar);

		if (verifica_mensaje(operacion_a_realizar, &mensaje_verificado) == 0) {
			ejecuta_calculo(mensaje_verificado, &solucion);
		} else {
			solucion[0] = 'N';
			solucion[1] = 'O';

		}

		// bzero(operacion_a_realizar,sizeof(operacion_a_realizar));

		//verifica_mensaje (operacion_a_realizar, &mensaje_verificado);

		//ejecuta_calculo (mensaje_verificado, &solucion);

		if (tcp_flag) {
			if (write(sconn, solucion, sizeof(solucion)) < 0) {
				perror("tcp server fallo write");
			}

			close(sconn);
			//shutdown(sconn, SHUT_RDWR);

			//sconn = -1;
		} else

		{
			sendto(s, solucion, sizeof(solucion), 0, &dirCli, sizeof(dirCli));
		}
	}
	close(s);
}
