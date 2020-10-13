#include "client.h"

void error(char *msg) {
	write(2, msg, (int)strlen(msg));
	exit(1);
}

void error_validator(int argc) {
	char *msg = "usage: ./server PORT\n";

	if (argc != 2)
		error(msg);
}

void error_msg(char *msg) {
    perror(msg);
    exit(1);
}

int check_port(char **argv) {
	char *msg = "Invalid port number\n";
    int port = atoi(argv[1]);

	if (!port)
		error(msg);
    return port;
}
