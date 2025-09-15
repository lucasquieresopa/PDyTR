#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>  // Para strlen y otras funciones de cadenas
#include <unistd.h>  // Para read, write y otras funciones de E/S
#include <stdlib.h>  // Para exit y otras funciones estándar
#include <math.h>
#include <time.h>

void error(char *msg)
{
    perror(msg);
    exit(1);
}


int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(1);
    }

    // TOMA EL NÚMERO DE PUERTO DE LOS ARGUMENTOS
    portno = atoi(argv[2]);
	
    // CREA EL FILE DESCRIPTOR DEL SOCKET PARA LA CONEXIÓN
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // AF_INET - FAMILIA DEL PROTOCOLO - IPV4 PROTOCOLS INTERNET
    // SOCK_STREAM - TIPO DE SOCKET 
	
    if (sockfd < 0) 
        error("ERROR opening socket");
	
    // TOMA LA DIRECCIÓN DEL SERVIDOR DE LOS ARGUMENTOS
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    // LIMPIA LA ESTRUCTURA serv_addr
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
	
    // COPIA LA DIRECCIÓN IP Y EL PUERTO DEL SERVIDOR A LA ESTRUCTURA DEL SOCKET
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
	
    // DESCRIPTOR - DIRECCIÓN - TAMAÑO DIRECCIÓN
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
        error("ERROR connecting");


	FILE *fw = fopen("write_time.txt", "a");
	FILE *fr = fopen("read_time.txt", "a");


    // ENVÍA UN MENSAJE AL SOCKET
    for(int i = 1; i<5; i++){
    	
    	int bytes_to_send = (int)(pow(10, i)+0.5);
    	printf("%d\n", bytes_to_send);
    	char buffer_send[bytes_to_send]; 
		for(int i = 0; i<bytes_to_send; i++){
			buffer_send[i] = '1';
		}
		buffer_send[bytes_to_send] = '\0';
		
		clock_t tw0, tw1, tr0, tr1;
		
		
		int s;
		if(bytes_to_send > 10000) s = 10000;
		else s = bytes_to_send;
		
			
		for(int j = 0; j<(int)(ceil(bytes_to_send/s)); j++){
			
			// NOTA: esto funciona porque se envía de a 10^x
			// si se enviase p.e 65535 deberia trabajarse distinto
			// el último bloque para enviar la cantidad correcta
			
		
			tw0 = clock();
			n = write(sockfd, &buffer_send[s*j], s); 
			tw1 = clock();
			double tw = ((double)(tw1-tw0))/CLOCKS_PER_SEC;
			
			fprintf(fw, "%f\n", tw);
			
			

			printf("Se enviaron: %d/%d bytes\n", n, bytes_to_send);
			if (n < 0) {
			    error("ERROR writing to socket");
				break;
			}	
			
			
			char buffer_recv[256];
			// ESPERA RECIBIR UNA RESPUESTA
			tr0 = clock();
			n = read(sockfd, buffer_recv, 255);
			tr1 = clock();
			double tr = ((double)(tr1-tr0))/CLOCKS_PER_SEC;
			
			fprintf(fr, "%f\n", tr);

			
			
			buffer_recv[256] = '\0';
			printf("Here is the message: %s\n", buffer_recv);
			//printf("Se recibieron: %d bytes\n", n);
			if (n < 0) {
				error("ERROR reading from socket");
				break;	 
			}
			bzero(buffer_recv, 256); // borra memoria asignada
		
		}
		
				
	}
	
	fclose(fr);
	fclose(fw);
    // CIERRA EL SOCKET
    close(sockfd);

    return 0;
}
