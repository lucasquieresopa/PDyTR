#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <puerto>\n", argv[0]);
        exit(1);
    }

    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char *buffer;
    struct sockaddr_in serv_addr, cli_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) error("ERROR al abrir socket");

    memset(&serv_addr, 0, sizeof(serv_addr));
    portno = atoi(argv[1]);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR en bind");

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0) error("ERROR en accept");
	
	for (int exp = 1; exp <= 6; exp++) {
		size_t n = 1;
		for (int i=0; i<exp; i++) n *= 10;  // 10^exp

		buffer = malloc(n);
		if (!buffer) error("malloc");
		
		size_t total = 0;
	
		// En este bucle se leen los datos en varias iteraciones
		while (total < n){
			ssize_t r = read(newsockfd, buffer + total, n - total);
			if (r < 0) error("Read");
			if (r == 0) break;
			total += (ssize_t)r;
			printf("Leyendo cantidad: %zu\n", r);
		}

		printf("Servidor: recibido bloque de 10^%d = %zu bytes\n", exp, total);
		
		
		// CONFIRMACIÓN DE RECEPCIÓN
		
		int w = write(newsockfd, "Se recibio el mensaje\0", 23);
		if (w < 0) error("ERROR writing to socket");

		free(buffer);
	}
	
		
    close(newsockfd);
    close(sockfd);
    return 0;
}
