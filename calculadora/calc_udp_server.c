#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


struct sockaddr_in dirMia;
struct sockaddr_in dirCli;
char mensajeRec[200];
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
		rec= recvfrom (s,mensajeRec,sizeof(mensajeRec), 0, &dirCli, &tam);
		sendto (s,mensajeRec,rec,0,&dirCli,sizeof(dirCli));
	}
}