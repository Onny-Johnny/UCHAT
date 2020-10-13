#include "server.h"

int mx_create_log() {
	int fd = 0;

	fd = open("userver.log", O_CREAT | O_RDWR | O_APPEND, S_IREAD | S_IWRITE);
	if (fd < 0)
		error_msg("fd");
	return fd;
}

void logsescr(t_client *client) {
    write(client->log_sescr, "User connected from client ", 27);
    write(client->log_sescr, mx_itoa(client->socket), 1);
    write(client->log_sescr, "\n", 1);
}

void accepting(t_client *client) {
    write(client->log_sescr, "User connected from client ", 27);
    write(client->log_sescr, mx_itoa(client->socket), 1);
    write(client->log_sescr, "\n", 1);
}
