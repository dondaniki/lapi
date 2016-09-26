#include "calculadora.h"

struct sockaddr_in dirServ;
char mensajeEnv[100];
char mensajeRec[200];

char operando[3];
char solucion[3];


int rec;
int s;

main (int argc, char *argv[])
{
  int udp_flag = 0;
  int tcp_flag = 0;
  int multi_flag = 0;
  int port_number = 7777;
  char *pvalue = NULL;
  char *pcalc = NULL;
  char *pserv = NULL;
  int index;
  int c;

  if (argc == 1)
    {

      printf ("Usage calculadora_IP_client [-u|-t] [ -p port ] -s server -o operacion");

      exit (1);
    }

  opterr = 0;
  while ((c = getopt (argc, argv, "tup:o:s:")) != -1)
    switch (c)
      {
      case 't':
	tcp_flag = 1;
	break;
      case 'u':
	udp_flag = 1;
	break;
      case 'p':
	pvalue = optarg;
	break;
      case 's':
	pserv = optarg;
	break;
      case 'o':
	pcalc = optarg;
	break;
      default:
	      printf ("Usage calculadora_IP_client [-u|-t] [ -p port ] -s server -o operacion");

	      exit (1);
      }

  // if ( isdigit(atoi(pvalue)))

  if (pvalue != NULL)
    {
      int length = strlen (pvalue);
      for (int i = 0; i < length; i++)
	if (!isdigit(pvalue[i]))
	  {
	    printf ("Entered port is not a number\n");
	    exit (1);
	  }

      port_number = atoi (pvalue);

      if (!((port_number > 1024) && (port_number < 65535)))
	{
	  printf ("puerto fuera de rango\n");
	  exit (1);
	}
    }
  if ((tcp_flag == udp_flag) && (udp_flag == 1))
    {
      printf ("Especifique UDP o TCP \n");
      exit (1);
    }
  if ((tcp_flag == 0) && (udp_flag == 0))
    {
      //el modo por defecto tcp
      tcp_flag = 1;
    }

  if (pcalc == NULL)
    {
      printf ("debe escribir una operacion segun protocolo\n");
      exit (1);
    }

  if ((pserv == NULL))
    {
      printf ("debe escribir una ip del servidor\n");
      exit (1);
    }
  else
    {
      struct in_addr addr;
      if (inet_aton(pserv, &addr) == 0) {
          fprintf(stderr, "Invalid IP address\n");
          exit(EXIT_FAILURE);
      }

    }

  printf ("udp_flag = %d, tcp_flag = %d\n", udp_flag, tcp_flag );
  printf ("port_number = %d\n", port_number);
  if (pcalc != NULL ) printf ("operacion = %s\n", pcalc);
  if (pserv != NULL ) printf ("ip = %s\n", pserv);

  //return 0;


  if(tcp_flag)
    {
      s = socket (AF_INET, SOCK_STREAM, 0);

    }
  else
    {

      s = socket (AF_INET, SOCK_DGRAM, 0);

    }
  dirServ.sin_family = AF_INET;
  dirServ.sin_addr.s_addr = inet_addr (pserv);
  dirServ.sin_port = htons (port_number);


  if(tcp_flag) connect (s,&dirServ,sizeof(dirServ));

  //strcpy (mensajeEnv,"hola amigo");
  //operando[0]='+';
  //operando[0]='-';
  //operando[0]='*';
  //operando[0] = '/';
  //operando[1] = '3';
  //operando[2] = '8';

  memcpy(operando, pcalc, sizeof(operando));



  if(tcp_flag)
    {
      write (s,operando,strlen(operando));
    }
  else
    {
  //sendto (s,mensajeEnv,strlen(mensajeEnv),0,&dirServ,sizeof(dirServ));
  sendto (s, operando, strlen (operando), 0, &dirServ, sizeof(dirServ));
    }



  int tam = sizeof(dirServ);
  if (tcp_flag)
    {
      int tot=strlen(operando);
      int n=0;
      while (n<tot){
      rec= read (s,solucion+n,tot-n);
      n+= rec;
      }
    }
  else
    {
      rec = recvfrom (s, solucion, sizeof(solucion), 0, &dirServ, &tam);
    }


  mensajeRec[rec] = '\0';
  printf ("recibido :%s:\n", solucion);

}
