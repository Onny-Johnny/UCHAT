#include "server.h"

struct sockaddr_in init_serv_address(int listening_socket, int port, int enable) {
    struct sockaddr_in serv_addr;

    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family      = AF_INET;           // <del> семейство адрессов.
    serv_addr.sin_addr.s_addr = INADDR_ANY; // <del> адресс IPv4 PS. INADDR_ANY это вроже любой доступный локальный адресс (это не точно)
    serv_addr.sin_port        = htons(port);       // <del> номер порта
    setsockopt(listening_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&enable, sizeof(int));
    return serv_addr;
}


int main(int argc, char **argv) {
	int port = 0;
    struct sockaddr_in serv_addr;
	int listen_fd = 0;
    int enable = 0;

    error_validator(argc);
    port = check_port(argv);
    make_demon();
    t_client *client = create_client();
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd < 0)
        error_msg("Creating socket error");
    else
        logsescr(client);
    serv_addr = init_serv_address(listen_fd, port, enable);
    if (bind(listen_fd, (struct  sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error_msg("Bind error");
    printf("%s\n", "bind+");
	listen(listen_fd, 10);
    if (listen_fd < 0)
        printf("%s\n", "test fd after listening");
    client->db = connect_db(client->db);
    create_table_db(client->db);
    server_loop(client, listen_fd);
    sqlite3_close(client->db);
    close(client->socket);
}
