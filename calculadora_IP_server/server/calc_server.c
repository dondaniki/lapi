#include "calculadora.h"

struct sockaddr_in server_addr;
struct sockaddr_in client_addr;

char operacion_a_realizar[4];
char mensaje_verificado[3];
char solucion[2];


int rec;
int sock_srv;
#define CLIENT_MAX=1024;


int main(int argc, char *argv[]) {
	int udp_flag = 0;
	int tcp_flag = 0;
	int numero_clientes=0;
	int port_number = 7777;
	char *port_arg_value = NULL;

	int opcion;

	if (argc == 1) {

		printf("Usage calculadora_IP_server [-u|-t] [ -p port ]\n");

		exit(1);
	}

	opterr = 0;
	while ((opcion = getopt(argc, argv, "tup:")) != -1)
		switch (opcion) {
		case 't':
			tcp_flag = 1;
			break;
		case 'u':
			udp_flag = 1;
			break;
		case 'p':
			port_arg_value = optarg;
			break;
		default:
			printf("Usage calculadora_IP_server [-u|-t] [ -p port ]\n");

			exit(1);
			;
		}

	// if ( isdigit(atoi(port_arg_value)))

	if (port_arg_value != NULL) {

		int length = strlen(port_arg_value);
		for (int i = 0; i < length; i++)
			if (!isdigit(port_arg_value[i])) {
				printf("Entered port is not a number\n");
				exit(1);
			}

		port_number = atoi(port_arg_value);

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
			tcp_flag, port_arg_value);

	printf("udp_flag = %d, tcp_flag = %d\n", udp_flag, tcp_flag);
	printf("port_number = %d\n", port_number);

	if (tcp_flag) {
		sock_srv = socket(AF_INET, SOCK_STREAM, 0);
	} else {
		sock_srv = socket(AF_INET, SOCK_DGRAM, 0);

	}

	server_addr.sin_family = AF_INET;
	/* server_addr.sin_addr.s_addr= inet_addr ("127.0.0.1"); */
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(port_number); /* servidor de echo */

	//a sustituir por funcion wrapper
	if (bind(sock_srv, &server_addr, sizeof(server_addr)) <0)
	{
		perror("no se puede hacer bind en server, se sale");
		exit(-1);
	}

	if (tcp_flag) {
		listen(sock_srv, 2);
	}

	while (1) {




		bzero(&client_addr, sizeof(client_addr));
		int tam = sizeof(client_addr);
		int socket_efimero;
retorno_fallo_accept:
retorno_task_server:

		if (tcp_flag) {
			socket_efimero = accept(sock_srv, &client_addr, &tam);

			if(socket_efimero < 0)
			{
				perror("error en accept en servidor");

				goto retorno_fallo_accept;
			}

			if ( task_server_tcp(socket_efimero) == -1 )
				goto retorno_task_server;
			close(socket_efimero);

		} else {

			if (task_server_udp(sock_srv) == -1 )
					goto retorno_task_server;

		}

	}
	close(sock_srv);




}
