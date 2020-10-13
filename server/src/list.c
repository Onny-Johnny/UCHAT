#include "server.h"

t_client *create_client() {
    t_client *client = malloc(sizeof(t_client));

    client->socket = 0;
    client->log_sescr = mx_create_log();
    client->index = 0;
    client->db = 0;
    client->prev = NULL;
    client->next = NULL;
    return client;
}
