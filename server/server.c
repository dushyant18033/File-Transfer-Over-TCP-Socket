/*
server.c : CN HW1

NAME: Dushyant Panchal
ROLL NO.: 2018033
*/



#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>

#define PORT 9001

/*
These functions we will use in order
1) socket
2) bind
3) listen
4) accept
5) read/send ...
6) close
*/

int main()
{
	struct sockaddr_in server;
	//Specify which protocols to used 
	server.sin_family = AF_INET;			//For IPV4
	server.sin_port = htons(PORT);			//Port
	server.sin_addr.s_addr = INADDR_ANY;	//Server host IP


	int addressLen = sizeof(server);
	

	//socket(DOMAIN, TYPE, PROTOCOL) and returns socket FD
	int socketId = socket(AF_INET, SOCK_STREAM, 0);	
	//AF_INET==IPV4 (AF_INET6==IPV6), SOCK_STREAM==TCP (SOCK_DGRAM==UDP)

	
	//Binding port with address
	bind(socketId, (struct sockaddr *)&server, addressLen);


	//Lets wait for a client(s)
	//listen(socketFD, backlogs)
	listen(socketId, 0);
	printf("Server ready\n");


	//Accepting connection
	int client = accept(socketId, (struct sockaddr *)&server, (socklen_t *)&addressLen);

	
	//Store filename recv from the client
	char fileToSend[1024]={0};
	printf("Client Connected \n");
	read(client, fileToSend, 1024);
	printf("Client asked for: %s\n", fileToSend);



	FILE* readfp;
	unsigned char buf[1024];

	if(readfp = fopen(fileToSend,"rb"))		//If the requested file exists
	{
		printf("File found!\n");

		buf[0]='y';
		send(client, buf, 1, 0);	//Send 1 byte msg for file exists
		buf[0]=0;


		printf("Now Sending ...");	//Proceed with sending of the file
		
		size_t size;
		while( (size = fread(buf, 1, sizeof(buf), readfp) ) > 0)
		{
			send(client, buf, size, 0);
			printf(".");
		}
		fclose(readfp);


		printf("\nFile sent!\n");
	}
	else	//If file doesn't exist
	{
		printf("\nThe requested file does not exist.\n");
		buf[0]='n';
		send(client, buf, 1, 0);	//Send 1 byte msg for file doesn't exists
	}


	//Closing the connection
	printf("Closing connection!\n");
	close(client);
	close(socketId);

	return 0;
}