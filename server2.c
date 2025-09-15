/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>   // Para exit, atoi y otras funciones estándar
#include <string.h>   // Para bzero y otras funciones de cadenas
#include <unistd.h>   // Para read, write y otras funciones de E/S
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <math.h>
#include <time.h>

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;

     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
	 
	 // CREA EL FILE DESCRIPTOR DEL SOCKET PARA LA CONEXIÓN
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
	 // AF_INET - FAMILIA DEL PROTOCOLO - IPV4 PROTOCOLS INTERNET
	 // SOCK_STREAM - TIPO DE SOCKET 
	 
     if (sockfd < 0) 
        error("ERROR opening socket");
		
     // LIMPIA LA ESTRUCTURA serv_addr
     bzero((char *) &serv_addr, sizeof(serv_addr));
     
     // ASIGNA EL PUERTO PASADO POR ARGUMENTO
     // ASIGNA LA IP EN DONDE ESCUCHA (SU PROPIA IP)
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
	 
	// VINCULA EL FILE DESCRIPTOR CON LA DIRECCIÓN Y EL PUERTO
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
			  
     // SETEA LA CANTIDAD QUE PUEDEN ESPERAR MIENTRAS SE MANEJA UNA CONEXIÓN
     
     listen(sockfd, 5);
	 
	 // SE BLOQUEA A ESPERAR UNA CONEXIÓN
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
				 
     // DEVUELVE UN NUEVO DESCRIPTOR POR EL CUAL SE VAN A REALIZAR LAS COMUNICACIONES
	 if (newsockfd < 0) 
          error("ERROR on accept");
		  
     bzero(buffer, 256);


	//FILE *f = fopen("read_time.txt", "a");

	// ENVIO Y RECEPCION DE MENSAJE
	for(int i = 1; i<5; i++){
	
		int bytes_to_recv = (int)(pow(10, i)+0.5);
		printf("%d\n", bytes_to_recv);
		
	
		
		int s;
		if(bytes_to_recv > 10000) s = 10000;
		else s = bytes_to_recv;
		
		char buffer[s];
		
		printf("PORCIONES A RECIBIR: %d\n",(int)ceil(bytes_to_recv/s));
		for(int j = 0; j<(int)(ceil(bytes_to_recv/s)); j++){
			
			// NOTA: esto funciona porque se envía de a 10^x
			// si se enviase p.e 65535 deberia trabajarse distinto
			// el último bloque para enviar la cantidad correcta
	
			n = read(newsockfd, buffer, sizeof(buffer));
	
			if (n < 0){
				error("ERROR reading from socket");
				break;
			}
			printf("Se recibieron: %d/%d bytes\n", n, bytes_to_recv);
			
			
			n = write(newsockfd, "I got your message", 18);
			if (n < 0) error("ERROR writing to socket");
		
		
		}
		
		
		/*
		
		//clock_t t0, t1;
		int total_recv = 0; // s = total_sent
		while(total_recv < s){
			// LEE EL MENSAJE DEL CLIENTE
			
			
			//t0 = clock();
			n = read(newsockfd, buffer, sizeof(buffer));
			//t1 = clock();
			//double t = ((double)(t1-t0))/CLOCKS_PER_SEC;
			
			//fprintf(f, "%f\n", t);
			
			total_recv += n;
			buffer[s] = '\0';
			if (n < 0){
				error("ERROR reading from socket");
				break;
			}
			//printf("Here is the message: %s\n", buffer);
			printf("Se recibieron: %d/%d bytes\n", n, s);
		 	
			
			// RESPONDE AL CLIENTE
			
			n = write(newsockfd, "I got your message", 18);
			//printf("Se enviaron: %d bytes\n", n);
			if (n < 0) error("ERROR writing to socket");
		}
		*/
	}
	
	//fclose(f);
    // CIERRA LOS SOCKETS
    close(newsockfd);
    close(sockfd);
	
     return 0; 
}
