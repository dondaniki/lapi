#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


struct sockaddr_in dirMia;
struct sockaddr_in dirCli;
char mensajeRec[200];

char operacion_a_realizar[4];
char solucion[2];

char operador='0';
int operando1=0;
int operando2=0;

int resultado_parcial=0;



int rec;
int s;

main (int argc, char *argv[])
{
	s=socket (AF_INET, SOCK_DGRAM,0);

	dirMia.sin_family= AF_INET;
	/* dirMia.sin_addr.s_addr= inet_addr ("127.0.0.1"); */
	dirMia.sin_addr.s_addr= INADDR_ANY;
	dirMia.sin_port= htons (7777) ; /* servidor de echo */
	bind (s,&dirMia,sizeof(dirMia));

	while (1) {
		bzero (&dirCli,sizeof(dirCli));
		int tam= sizeof (dirCli);
		rec= recvfrom (s,operacion_a_realizar,sizeof(operacion_a_realizar), 0, &dirCli, &tam);


		operacion_a_realizar[rec]='\0';
		printf ("recibido server:%s:\n",operacion_a_realizar);


		//operaciones de calculo
		operador=operacion_a_realizar[0];
		operando1=operacion_a_realizar[1]-'0';
		operando2=operacion_a_realizar[2]-'0';

		printf("%c\n", operacion_a_realizar[0] );
		printf("%d\n", operando1 );
		printf("%d\n", operando2 );


		switch (operador) {
			case '+':
						resultado_parcial = ( operando1 ) + ( operando2 );
								printf("%d\n", resultado_parcial );
			break;
			case '-':
						resultado_parcial = ( operando1 ) - ( operando2 );
								printf("%d\n", resultado_parcial );
			break;
			case '*':
						resultado_parcial = ( operando1 ) * ( operando2 );
								printf("%d\n", resultado_parcial );
			break;
			case '/':
						resultado_parcial = ( operando1 ) / ( operando2 );
								printf("%d\n", resultado_parcial );
			break;
		}


		//presentacion del resultado_parcial
		if( resultado_parcial > 10)
		{
			solucion[0]=(resultado_parcial / 10) + '0';
			solucion[1]=(resultado_parcial % 10) + '0';
		}
		if ( resultado_parcial < 0)
		{
			solucion[0]='-';
			solucion[1]='0' + abs(resultado_parcial);
		}



	//	printf("%d\n", resultado_parcial );


		sendto (s,solucion,sizeof(solucion),0,&dirCli,sizeof(dirCli));
	}
}
