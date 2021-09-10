#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <netinet/in.h>

char message[] = "Hello there!\n";
char buf1[sizeof(message)];
int fs, fr;

int main() {
	int sock;
	struct sockaddr_in addr;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	
	if (sock < 0) {
		perror("socket");
		exit(1);
	}
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(3425);
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	
	if (connect(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
		perror("connect");
		exit(2);
	}
	
	fs = send(sock, message, sizeof(message), 0);
	fr = recv(sock, buf1, sizeof(message), 0);
	printf("Server: %s", buf1);
	
	
	/*---------------------- Close Server code. ----------------------*/
	int ch;
	char new_message[] = "stop";
	
	printf("\nClose Server? (1/0): ");
	scanf("%d", &ch);
	
	if (ch == 1) {
		fs = send(sock, new_message, sizeof(new_message), 0);
		printf("\nServer has been stoped.\n");
	}
	
	close(sock);
	
	return 0;
}

// Created by RIDOS 
	
