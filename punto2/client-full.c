#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/time.h>

void error(const char *msg) {
    perror(msg);
    exit(0);
}

double dwalltime(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
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
    
    
    
    double w0, w1, r0, r1;
    
    FILE *write_file = fopen("write_time.txt", "a");
	FILE *read_file = fopen("read_time.txt", "a");
    

    for (int exp = 1; exp <= 6; exp++) {
        size_t n = 1;
        for (int i=0; i<exp; i++) n *= 10;  // 10^exp

        char *buffer = malloc(n);
        if (!buffer) error("malloc");

        memset(buffer, 'X', n);  // llena con datos 

		
		// ENVÍO
		w0 = dwalltime()();
        int w = write(sockfd, buffer, n);
		w1 = dwalltime();
		double write_time = w1-w0 // CLOCKS_PER_SEC;
        
        if (w < 0) error("write");

        printf("Cliente: enviado bloque de 10^%d = %zu bytes\n", exp, w);
        fprintf(write_file, "%f\n", write_time);
        
        
        
        // RECEPCIÓN
        char *buffer_recv = malloc(256);
        r0 = dwalltime();
		int r = read(sockfd, buffer_recv, 255);
		r1 = dwalltime();
		double read_time = (r1-r0) //CLOCKS_PER_SEC;
		
		


		if (r < 0) {
			error("ERROR reading from socket");
			break;	 
		}
		printf("El mensaje recibido es: %s\n", buffer_recv);
		fprintf(read_file, "%f\n", read_time);


        free(buffer);
        free(buffer_recv);
    }
    
    fclose(write_file);
    fclose(read_file);
    close(sockfd);
    return 0;
}
