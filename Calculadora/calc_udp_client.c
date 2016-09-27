#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

struct sockaddr_in dirServ;
char mensajeEnv[100];
char mensajeRec[200];

char operando[3];


int rec;
int s;

main (int argc, char *argv[])
{
	s=socket (AF_INET, SOCK_DGRAM,0);
	dirServ.sin_family= AF_INET;
	dirServ.sin_addr.s_addr= inet_addr ("127.0.0.1");
	dirServ.sin_port= htons (7777) ; /* servidor de echo */



	//strcpy (mensajeEnv,"hola amigo");
	//operando[0]='+';
	//operando[0]='-';
	//operando[0]='*';
	operando[0]='/';
	operando[1]='3';
	operando[2]='8';
	//sendto (s,mensajeEnv,strlen(mensajeEnv),0,&dirServ,sizeof(dirServ));
	sendto (s,operando,strlen(operando),0,&dirServ,sizeof(dirServ));

	int tam= sizeof (dirServ);
	rec= recvfrom (s,mensajeRec,sizeof(mensajeRec), 0, &dirServ, &tam);



	mensajeRec[rec]='\0';
	printf ("recibido :%s:\n",mensajeRec);

}
