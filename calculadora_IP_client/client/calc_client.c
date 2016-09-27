#include "calculadora.h"

struct sockaddr_in sock_srv;
char mensajeEnv[100];
char mensajeRec[200];

char problem_to_send[3];
char server_solution[3];

int rec;
int local_socket;

char ipstr[INET6_ADDRSTRLEN];

int main(int argc, char *argv[]) {
	int udp_flag = 0;
	int tcp_flag = 0;
	//int multi_flag = 0;
	int port_number = 7777;
	char *rem_port_val = NULL;
	char *server_ip_addr = NULL;
	char *problem_2_solve = NULL;
	//int index;
	int c;

	if (argc == 1) {

		printf(
				"Usage calculadora_IP_client [-u|-t] [ -p port ] -s server -o operacion");

		exit(1);
	}

	opterr = 0;
	while ((c = getopt(argc, argv, "tup:o:s:")) != -1)
		switch (c) {
		case 't':
			tcp_flag = 1;
			break;
		case 'u':
			udp_flag = 1;
			break;
		case 'p':
			rem_port_val = optarg;
			break;
		case 's':
			server_ip_addr = optarg;
			break;
		case 'o':
			problem_2_solve = optarg;
			break;
		default:
			printf(
					"Usage calculadora_IP_client [-u|-t] [ -p port ] -s server -o operacion");

			exit(1);
		}

	if (rem_port_val != NULL) {
		int length = strlen(rem_port_val);
		for (int i = 0; i < length; i++)
			if (!isdigit(rem_port_val[i])) {
				printf("Entered port is not a number\n");
				exit(1);
			}

		port_number = atoi(rem_port_val);

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

	if (problem_2_solve == NULL) {
		printf("debe escribir una operacion segun protocolo\n");
		exit(1);
	}

	if ((server_ip_addr == NULL)) {
		printf("debe escribir una ip del servidor\n");
		exit(1);
	} else {
		struct in_addr addr;
		if (inet_aton(server_ip_addr, &addr) == 0) {
			fprintf(stderr, "Invalid IP address\n");
			exit(EXIT_FAILURE);
		}

	}

	printf("udp_flag = %d, tcp_flag = %d\n", udp_flag, tcp_flag);
	printf("port_number = %d\n", port_number);
	if (problem_2_solve != NULL)
		printf("operacion = %s\n", problem_2_solve);
	if (server_ip_addr != NULL)
		printf("ip = %s\n", server_ip_addr);

	//return 0;

	if (tcp_flag) {
		local_socket = socket(AF_INET, SOCK_STREAM, 0);

	} else {

		local_socket = socket(AF_INET, SOCK_DGRAM, 0);

	}
	sock_srv.sin_family = AF_INET;
	sock_srv.sin_addr.s_addr = inet_addr(server_ip_addr);
	sock_srv.sin_port = htons(port_number);

	if (tcp_flag) {
		socklen_t len;
		struct sockaddr_storage addr;
		int port;

		len = sizeof sock_srv;
		getpeername(local_socket, (struct sockaddr*) &sock_srv, &len);

		// deal with both IPv4 and IPv6:
		if (sock_srv.sin_family == AF_INET) {
			struct sockaddr_in *local_socket = (struct sockaddr_in *) &sock_srv;
			port = ntohs(local_socket->sin_port);
			inet_ntop(AF_INET, &local_socket->sin_addr, ipstr, sizeof ipstr);
		} else { // AF_INET6
			struct sockaddr_in6 *local_socket = (struct sockaddr_in6 *) &addr;
			port = ntohs(local_socket->sin6_port);
			inet_ntop(AF_INET6, &local_socket->sin6_addr, ipstr, sizeof ipstr);
		}

		if (connect(local_socket, &sock_srv, sizeof(sock_srv)) != 0) {

			perror("fallo en connect");
			printf("no se puede conectar contra %s\n", ipstr);
			exit(-1);
		} else {

			printf("Peer IP address: %s\n", ipstr);
		}
	}

	bzero(problem_to_send, sizeof(problem_to_send));
	memcpy(problem_to_send, problem_2_solve, sizeof(problem_2_solve));

	if (tcp_flag) {
		int n = write(local_socket, problem_to_send, strlen(problem_to_send));
		if (n < 0) {
			perror("fallo en tcp write\n");
			exit(-1);
		}
	} else {

		sendto(local_socket, problem_to_send, strlen(problem_to_send), 0, &sock_srv, sizeof(sock_srv));
	}

	if (tcp_flag) {

		int tot = (sizeof(char) * 2);
		int n = 0;
		while (n < tot) {
			rec = read(local_socket, server_solution + n, tot - n);
			n += rec;
		}
	} else {

		int tam = sizeof(sock_srv);
		rec = recvfrom(local_socket, server_solution, sizeof(server_solution), 0, &sock_srv, &tam);
	}

	mensajeRec[rec] = '\0';
	printf("recibido :%s:\n", server_solution);

}
