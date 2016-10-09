#include "calculadora.h"

int verifica_mensaje(char * msg_2_check, char * sol) {
	char operador, operando1, operando2;
	int resultado_parcial = 0;
	unsigned short int error = 0;
	char solucion[3];

	if (msg_2_check == NULL || msg_2_check[0] == '\0')
		return -1;
	if (sol == NULL)
		return -1;

	//operaciones de calculo
	operador = msg_2_check[0];
	operando1 = msg_2_check[1] - '0';
	operando2 = msg_2_check[2] - '0';

	if ((operando1 < 0 || operando1 > 9)) {
		error = 1;
	}

	if ((operando2 < 0 || operando2 > 9)) {
		error = 1;
	}

	if ((operador != '/') && (operador != '+') && (operador != '-')
			&& (operador != '*')) {
		error = 1;
	}

	if (error) {
		return -1;
	} else {
		printf("%c\n", msg_2_check[0]);
		printf("%d\n", operando1);
		printf("%d\n", operando2);

		solucion[0] = operador;
		solucion[1] = operando1;
		solucion[2] = operando2;

		memcpy(sol, solucion, sizeof(solucion));

		return 0;
	}
}
