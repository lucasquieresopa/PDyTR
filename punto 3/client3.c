#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>

void error(const char *msg) {
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr,"Uso: %s <hostname> <puerto>\n", argv[0]);
        exit(0);
    }

    int sockfd, portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) error("ERROR al abrir socket");

    server = gethostbyname(argv[1]);
    if (!server) {
        fprintf(stderr,"ERROR, host inexistente\n");
        exit(0);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
	
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) error("ERROR en connect");
    
    
    
    clock_t t0, t1, t;
    
    FILE *t_file = fopen("pingpong.txt", "a");

    

    for (int exp = 1; exp <= 6; exp++) {
        size_t n = 1;
        for (int i=0; i<exp; i++) n *= 10;  // 10^exp

        char *buffer = malloc(n);
        if (!buffer) error("malloc");

        memset(buffer, 'X', n);  // llena con datos 

		
		// ENVÍO
		t0 = clock();
        int w = write(sockfd, buffer, n);

        
        if (w < 0) error("write");

        printf("Cliente: enviado bloque de 10^%d = %zu bytes\n", exp, w);

        
        
        
        // RECEPCIÓN

		int r = read(sockfd, buffer, n);
		t1 = clock();
		double t = ((double)(t1-t0))/CLOCKS_PER_SEC;
		
		


		if (r < 0) {
			error("ERROR reading from socket");
			break;	 
		}
		printf("Recibi: %d bytes", r);
		printf("\nPING PONG: %lf\n\n", t);
		fprintf(t_file, "%f\n", t);

		

        free(buffer);
 
    }
    
    close(t_file);
    close(sockfd);
    return 0;
}
