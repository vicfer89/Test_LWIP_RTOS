/*
 * Sockets_UDP.h
 *
 *  Created on: 11 sept. 2021
 *      Author: Vic
 */

#ifndef INC_SOCKETS_UDP_H_
#define INC_SOCKETS_UDP_H_

#include "lwip.h"
#include "lwip/api.h"
#include "lwip/sockets.h"
#include "stdint.h"

int Eth_UDP_Init(int port);
long UDP_Send(int sd, char *buf, int buflen, char *ipdest, int portdest);
long UDP_Recv(int sd, uint8_t *buf, int buflen);
long UDP_Listen (int sd);
long UDP_RecvFrom(int sd, uint8_t *buf, int buflen, struct sockaddr_in *src_addr, socklen_t * addrlen);
int Eth_UDP_End(int sd);

#endif /* INC_SOCKETS_UDP_H_ */
