/*
 * Sockets_UDP.c
 *
 *  Created on: 11 sept. 2021
 *      Author: Vic
 */

#include "../Inc/Sockets_UDP.h"

/*
 * Inicializa los sockets para UDP
 *
 * */
int Eth_UDP_Init(int port)
{
	int on = 1; // On value for SO_BROADCAST

	struct sockaddr_in sockin;

	int sd = socket(AF_INET, SOCK_DGRAM, 0); // Init a Socket descriptor
	memset((uint8_t *) &sockin, 0, sizeof(sockin)); // Reset all sockin values to zero
	sockin.sin_family = AF_INET;
	sockin.sin_port = htons(port); // htons() converts int to host port information
	/* Bind a name to the socket */
	if( bind(sd, (struct sockaddr*) &sockin, sizeof(sockin)) == -1 )
	{
		printf("Error on socket binding: %d \n", port);
		return 0;
	}
	printf("Socket binded for port %d \n", port);

	/* Socket options:
	 * 	- SOL_SOCKET: To manipulate options at "Socket" level
	 * 	- SO_BROADCAST: To send data to more than one destination */
	setsockopt(sd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));

	return sd;	// returns socket descriptor
}

/*
 *  Envia información por un socket UDP
 *
 * */
long UDP_Send(int sd, char *buf, int buflen, char *ipdest, int portdest)
{

	struct sockaddr_in servaddr; // Destination descriptor

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(portdest);
	servaddr.sin_addr.s_addr = inet_addr(ipdest);

	return sendto(sd, buf, buflen, 0, (struct sockaddr*) &servaddr, sizeof(servaddr) );	// send to an specific source

}

/*
 * Recepción de datos por UDP
 *
 * */
long UDP_Recv(int sd, uint8_t *buf, int buflen)
{

	return recv(sd, buf, buflen, MSG_DONTWAIT); // Read data when available from all sources
}

/*
 * Inicializa escucha de un socket determinado
 *
 * */
long UDP_Listen (int sd)
{
	  int ret;
	  /* listen for incoming request on the specific socket */
	  if ((ret=listen(sd, 1)) == -1)
	  {
			  close(sd);
			  printf ("listen error: %s",strerror(errno));
	  }
	  return ret;
}


/*
 *
 * Función que devuelve información sobre la recepción de un paquete UDP
 *
 * */
long UDP_RecvFrom(int sd, uint8_t *buf, int buflen, struct sockaddr_in *src_addr, socklen_t * addrlen)
{

	if ( sd == 0 )
		return -1;

	return recvfrom(sd, buf, buflen, MSG_DONTWAIT, (struct sockaddr*) src_addr, addrlen); //read from a specific src_addr
}

/*
 * Cierra la conexión UDP
 *
 * */
int Eth_UDP_End(int sd)
{
	return close(sd); // terminates the connection
}
