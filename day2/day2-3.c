#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	printf("----------------------");
	int sockfd, len, s, n;
	struct sockaddr_in ca;
	char buf[1025];
	char scode[] = "HTTP/1.0 200 OK\n";
	char ctype[] = "Content-Type: text/html\n";
	char eoh[] = "\n";
	// char msg[] = "<html><body><h2>Simple HTML File</h2><p>This is a pen</p></body></html>\n";
	FILE *fp;
	//char fileToRead[] = "index.html";
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	ca.sin_family = AF_INET;
	ca.sin_addr.s_addr = htonl(INADDR_ANY);
	ca.sin_port = htons(atoi( argv[1] ));
	n = bind(sockfd, (struct sockaddr *)&ca, sizeof(ca));
	if (n == -1) { perror("bind"); exit(EXIT_FAILURE); }
	listen(sockfd, 5);

	while (1) {
			len = sizeof(ca);
			s = accept(sockfd, (struct sockaddr *)&ca, (socklen_t *)&len);
			if (s < 0) { perror("accept"); exit(EXIT_FAILURE); }
			if (fork() != 0) {
				close(s);
			}
			else {
				close(sockfd);
				printf("Connected from %s port %u\n", inet_ntoa(ca.sin_addr), ntohs(ca.sin_port));
				
				n = recv(s, buf, sizeof(buf), 0);
				buf[n] = 0;
				char fname[1025];
				printf("Received Request:\n%s\n", fname);

				char param1[1025], param2[1025];
				sscanf(buf, "%s %s", param1, param2);
				printf("FileName: %s\n", param2);
				if (strlen(param2) == 1) {
					strcpy( fname, "index.html" );
				}
				else {
					fname[0] = '\0';
					strcat( fname, "." );
					strcat( fname, param2 );
				}
				fp = fopen(fname, "r");
				if (fp == NULL)
				{
					// printf("File not found.\n");
					// return 1;
					strcpy(fname, "notfound.html");
					fp = fopen("notfound.html", "r");
				}

				send(s, scode, strlen(scode), 0);
				send(s, ctype, strlen(ctype), 0);
				send(s, eoh, strlen(eoh), 0);

				while ((n = fread( buf, 1, 1024, fp )) > 0) {
					send(s, buf, n, 0);
				}

				close(s);
				fclose(fp);
				return 0;
			}
		}
	return 0;
}
