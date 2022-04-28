#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUF_LEN 128

int main(int argc, char *argv[]){
	struct sockaddr_in server_addr, client_addr;
	int server_fd, client_fd;
	int len, msg_size;
	char buf[BUF_LEN + 1];

	if(argc != 2){
		printf("Usage: %s port\n", argv[0]);
		exit(0);
	}
	
	if((server_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0){
		printf("Server: Can't open stream socket.");
		exit(0);
	}

	bzero((char *)&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(atoi(argv[1]));

	if(bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
		printf("Server: Can't bind local address.\n");
		exit(0);
	}

	listen(server_fd, 5);
	while(1){
		printf("Server: waiting connection request.\n");
		len = sizeof(client_addr);

		client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &len);
		if(client_fd < 0){
			printf("Server: accept failed.\n");
			exit(0);
		}

		printf("Server: A client connected.\n");
		msg_size = read(client_fd, buf, sizeof(buf));
		write(client_fd, buf, msg_size);
		close(client_fd);
	}
	close(server_fd);
	return 0;
}
