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
	int s, n;
	int len_in, len_out;
	struct sockaddr_in server_addr;
	char buf[BUF_LEN + 1];

	if(argc != 3){
		printf("Usage: %s ip_address ip_portNumber\n", argv[0]);
		exit(0);
	}
	
	if((s = socket(PF_INET, SOCK_STREAM, 0)) < 0){
		printf("Can't create socket\n");
		exit(0);
	}

	bzero((char *)&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	server_addr.sin_port = htons(atoi(argv[2]));

	if(connect(s, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
		printf("Can't connect.\n");
		exit(0);
	}
	
	while(1){
		fputs("Input any string(q: Quit) ", stdout);
		fgets(buf, BUF_LEN, stdin);
		buf[BUF_LEN] = '\n';
		len_out = strlen(buf);
		
		if(!strcmp(buf, "q\n"))
			break;
		
		printf("Echoed string : %s", buf);
	}
	
	close(s);
	return 0;
}
