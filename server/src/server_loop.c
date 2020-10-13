#include "server.h"

static void sprint_table_json(cJSON *root) {
	char *out = cJSON_Print(root);
	printf("%s\n", out);
	free(out);
}


void *mx_chatfunc(void *data) {
	t_client *client = (t_client *)data;
	char buff[MX_BUFF_SIZE];
	// int currentfd = client->socket;
	cJSON *jobj = cJSON_CreateObject();
	int status = 0;

	while (1) {
		bzero(buff, MX_BUFF_SIZE);
		read(client->socket, buff, sizeof(buff));
		jobj = cJSON_Parse(buff);
		cJSON *json_type = cJSON_GetObjectItemCaseSensitive(jobj, "type");
		sprint_table_json(jobj);
		//printf("%s\n", json_type->valuestring);
		if (strcmp(json_type->valuestring, "reg_user") == 0)
			status = registration_user(client->db, jobj);
		else if (strcmp(json_type->valuestring, "log_user") == 0)
			status = login_user(client->db, jobj);
		else if (strcmp(json_type->valuestring, "save_message") == 0)
			status = save_message(client->db, jobj);
		else if (strcmp(json_type->valuestring, "change_login") == 0) {
			cJSON *json_profile = cJSON_GetObjectItemCaseSensitive(jobj, "profile");
			cJSON *json_cur_log = cJSON_GetObjectItemCaseSensitive(json_profile, "curr_user_login");
			cJSON *json_new_log = cJSON_GetObjectItemCaseSensitive(json_profile, "new_user_login");

			status = update_set_string_where_string_db(client->db, "users", "login", 
														json_new_log->valuestring, "login", 
														json_cur_log->valuestring);
		}
		else if (strcmp(json_type->valuestring, "change_pass") == 0) {
			cJSON *json_profile = cJSON_GetObjectItemCaseSensitive(jobj, "pass");
			cJSON *json_cur_log = cJSON_GetObjectItemCaseSensitive(json_profile, "curr_user_pass");
			cJSON *json_new_log = cJSON_GetObjectItemCaseSensitive(json_profile, "new_user_pass");

			status = update_set_string_where_string_db_pass(client->db, "users", "pass", 
														json_new_log->valuestring, "pass", 
														json_cur_log->valuestring);
		}
		write(client->socket, &status, 4);
		cJSON_Delete(jobj);
	}
}

void server_loop(t_client *client, int listen_fd) {
	struct sockaddr_in cli_addr;
	pthread_t thread = NULL;
	socklen_t cli_len = sizeof(cli_addr);

	while (1) {
        client->socket = accept(listen_fd, (struct sockaddr *) &cli_addr, &cli_len);
        if (client->socket < 0) //continue;
            error_msg("Accept Error");
        accepting(client);
        int err = pthread_create(&thread, NULL, mx_chatfunc, (void *)client);
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
		client->next = create_client();
        client->next->prev = client->prev;
        client = client->next;
    }
}
