#include "client.h"

void client_logged_in(GtkButton *butt, gpointer data) {
	(void)butt;
	t_gtk_components *gui = (t_gtk_components *)data;
	char *client_login = (char *)gtk_entry_get_text(GTK_ENTRY(gui->signin_form->login));
	char *client_password = hash((char *)gtk_entry_get_text(GTK_ENTRY(gui->signin_form->password)), gui->key);
	int status = 0;

	cJSON *jobj = cJSON_CreateObject();
	cJSON *user = cJSON_CreateObject();
	cJSON_AddItemToObject(jobj, "user", user);
	cJSON *j_login = cJSON_CreateString(client_login);
	cJSON *j_password = cJSON_CreateString(client_password);
	cJSON_AddItemToObject(jobj, "type", cJSON_CreateString("log_user"));
	cJSON_AddItemToObject(user, "login", j_login);
	cJSON_AddItemToObject(user, "pass", j_password);
	char *jdata = cJSON_Print(jobj);
	// send(gui->socketfd, jobj, sizeof(jobj), 0);
	write(gui->socketfd, jdata, strlen(jdata));

	cJSON_Delete(jobj);
	free(jdata);
	read(gui->socketfd, &status, 4);
	if (status == ST_UNLOG_USER) {
		show_dialog(GTK_WIDGET(gui->signup_form->w_signup), "Login failed!");
	}
	else if(status == ST_LOG_USER) {
		gtk_widget_hide(gui->signin_form->w_signin);
    	gtk_widget_show_all(gui->chat_form->w_chat);
    }
}
