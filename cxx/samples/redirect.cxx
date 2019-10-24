#include <iostream>
using namespace std;

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

#define PORT 9999

int main()
{
	int newfd;	/* new file descriptor */

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family    = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    int sockfd;
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
        cout << "socket creation failed" <<endl;
        exit(EXIT_FAILURE);
    }

    struct linger sl;
    sl.l_onoff = 0;		/* 1/0: non-zero value enables linger option in kernel */
    sl.l_linger = 0;	/* 0: timeout interval in seconds */
    setsockopt(sockfd, SOL_SOCKET, SO_LINGER, &sl, sizeof(sl));

    // Bind the socket with the server address
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,
            sizeof(servaddr)) < 0 )
    {
        cout << "bind failed" << endl;
        exit(EXIT_FAILURE);
    }
    listen(sockfd,10);
    int fd = accept(sockfd, nullptr,0);
    cout << " recv connection from fd=" << fd << endl;

    /* this new file will become the standard output */
	/* standard output is file descriptor 1, so we use dup2 */
	/* to copy the new file descriptor onto file descriptor 1 */
	/* dup2 will close the current standard output */

    /* Save current stdout for use later */
    int saved_stdout = dup(1); //

	dup2(fd, 1);
	int error(0);

	while (true) {
		sleep(2); // The following will be directed to socket

		socklen_t len = sizeof (error);
		error=0;
		int retval = getsockopt (fd, SOL_SOCKET, SO_ERROR, &error, &len);

		if (error == 0) {
			cout << "***  This goes to the standard output redict to socket.\n";
		} else {
			close(fd);
			break;
		}
	}

	/* Restore stdout */
	dup2(saved_stdout, 1);
	cout << "***  complete connection to socket. error=" << error << endl;;

	exit(0);
}

////////////////////////////////////////////////////////
#include <iostream>
using namespace std;

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

#define PORT 9999

int main(int argc, char **argv)
{
    struct sockaddr_in servaddr, clientaddr;
    int sockfd;
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&clientaddr, 0, sizeof(clientaddr));

    // Filling clientaddr information
    clientaddr.sin_family    = AF_INET; // IPv4
    clientaddr.sin_addr.s_addr = INADDR_ANY;

    // Filling server information
    servaddr.sin_family    = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    if (connect(sockfd,(const struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
    {
    	cout << " fails to connect to server" << endl;
    	exit(-1);
    }

    char buffer[1024];
	while (true) {
		int ret = recv(sockfd, buffer, 1024, 0);
		if (ret>0){
			buffer[ret]='\0';
			cout << "; recv msg:" << buffer << endl;
		} else {
			cout << "; recv msg error: ret=" << ret << endl;
			exit(-1);
		}
	}

	exit(0);
}













