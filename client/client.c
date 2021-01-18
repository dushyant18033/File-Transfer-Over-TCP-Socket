/*
client.c : CN HW1

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
2) connect
3) read/send ...
4) close
*/


int main()
{
	struct sockaddr_in server;
	//Specify which protocols to used 
	server.sin_family = AF_INET;    		 //For IPV4
	server.sin_port = htons(PORT);  		 //Port
	server.sin_addr.s_addr = INADDR_ANY;  	 //Remote host IP

	//For using on different machines 
	//server.sin_addr.s_addr = inet_addr("192.168.43.112"); 


	//Create socket FD
	//Returns -ve if error >= 0 otherwise known as socket FD
	int sockId = socket(AF_INET, SOCK_STREAM, 0);


	//Plug in to the socket(Connect to the server)
	connect(sockId, (struct sockaddr * )&server, sizeof(server));


	//Buffer to store filename
	char fileToRecv[1024];
	printf("You are now connected to dushyant18033 FileServer\n");
	printf("Enter the file name to download(with extension): ");
	scanf("%s", fileToRecv);


	//Send request with filename
	send(sockId, fileToRecv, strlen(fileToRecv), 0);
	printf("Request sent !\n");


	//Buffer for reading data
	unsigned char buf[1024];


	//Read 1 byte msg for file exist or not
	read(sockId, buf, 1);


	if(buf[0]=='y')	//If exists then retrieve it
	{
		printf("File exists\n");

		printf("Now Retrieving ...");

		FILE* writefp = fopen(fileToRecv,"wb");

		size_t size;
		while( (size = read(sockId, buf, 1024) ) > 0)
		{    
			fwrite(buf, 1, size, writefp);
			printf(".");
		}
		fclose(writefp);

		printf("\nFile recieved!\n");
	}
	else	//Otherwise tell the client that the file does not exist
	{
		printf("\nRequested File does not exist on the server\n");
	}


	//Closing the connection
	printf("Closing Connection\n");
	close(sockId);

	return 0;
}