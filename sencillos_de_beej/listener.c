/*
** listener.c -- Ejemplo de servidor de sockets de datagramas
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MYPORT 4950	// puerto al que conectarán los clientes
#define MAXBUFLEN 100

int main(void)
{
	int sockfd;

	struct sockaddr_in my_addr;	// información sobre mi dirección

	struct sockaddr_in their_addr;	 // información sobre la dirección del cliente

	int addr_len, numbytes;

	char buf[MAXBUFLEN];

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	my_addr.sin_family = AF_INET;	// Ordenación de bytes de máquina

	my_addr.sin_port = htons(MYPORT);	// short, Ordenación de bytes de la red

	my_addr.sin_addr.s_addr = INADDR_ANY; // rellenar con mi dirección IP

	memset(&(my_addr.sin_zero), '\0', 8); // poner a cero el resto de la estructura

	if (bind(sockfd, (struct sockaddr *)&my_addr,sizeof(struct sockaddr)) == -1) {
		perror("bind");
		exit(1);
	}

	addr_len = sizeof(struct sockaddr);

	if ((numbytes=recvfrom(sockfd,buf, MAXBUFLEN-1, 0,(struct sockaddr *)&their_addr, &addr_len)) == -1) {
		perror("recvfrom");
		exit(1);
	}

	printf("got packet from %s\n",inet_ntoa(their_addr.sin_addr));

	printf("packet is %d bytes long\n",numbytes);

	buf[numbytes] = '\0';

	printf("packet contains \"%s\"\n",buf);

	close(sockfd);

	return 0;
}