#include "client.h"

static int client_validator(int argc, char **argv) {
	char *msg1 = "usage: ./client ip_address port\n";
	char *msg2 = "Invalid port number\n";
	int port;

	if (argc != 3)
		error(msg1);
	port = atoi(argv[2]);
	if (!port)
		error(msg2);
	return port;
}



int main(int argc, char **argv) {
	int port = client_validator(argc, argv);

    struct hostent *server;
    // int enable = 0;

	int fdsocket = socket(AF_INET, SOCK_STREAM, 0);
	if (fdsocket < 0)
		error_msg("Error while creating socket");
    

    server = gethostbyname(argv[1]);
    if (server == NULL)
        error_msg("NO SUCH HOST\n");

	struct sockaddr_in serv_addr;
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr_list[0], (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(port);

    while (1) {
	   int res = connect(fdsocket, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
	   if (res < 0)
        	error_msg("Error while connection");
       init_app(argc, argv, fdsocket); 
    }
    close(fdsocket);
}
