#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <netinet/in.h>
#include <sqlite3.h>
#include <pthread.h>
#include "../../lib/cjson/inc/cJSON.h"
#include "../../datab/inc/dich.h"
#include <sys/types.h>
#include <sys/stat.h>

#define MX_BUFF_SIZE 1024
#define ST_UNREG_USER 0
#define ST_REG_USER 1
#define ST_UNLOG_USER 2
#define ST_LOG_USER 3
#define ST_UNSAVE_MSSG 4
#define ST_SAVE_MSSG 5
#define ST_UNCHANGE_LOGIN 6
#define ST_CHANGE_LOGIN 7
#define ST_UNCHANGE_PASS 8
#define ST_CHANGE_PASS 9

typedef struct 		s_client {
	int 			socket;
	int 			log_sescr;
	int 			index;
	sqlite3 		*db;
	struct s_client *prev;
	struct s_client *next;
} 					t_client;

void error(char *msg);
void error_msg(char *msg);
void error_validator(int argc);
int check_port(char **argv);
struct sockaddr_in init_serv_address(int listening_socket, int port, int enable);
char *mx_strnew(const int size);
char *mx_itoa(int number);
void logsescr(t_client *client);
int mx_create_log();
void *handle_client(void *client_socket);
void *mx_chatfunc(void *data);
void accepting(t_client *client);
t_client *create_client();
void create_socket(int listen_fd, t_client *client);
void server_loop(t_client *client, int listen_fd);
void binding(int listen_fd, struct sockaddr_in serv_addr, int port);
void *mx_chatfunc(void *data);
void make_demon();

#endif
