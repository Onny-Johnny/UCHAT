#include "client.h"

void change_login(GtkButton *button, gpointer data) {
	t_gtk_components *gui = (t_gtk_components *)data;
	(void)button;

	int status = 0;
	char *jdata = NULL;
	cJSON *jobj = cJSON_CreateObject();
	cJSON *profile = cJSON_CreateObject();
	cJSON *jlogin_old = cJSON_CreateString((char *)gtk_entry_get_text(GTK_ENTRY(gui->signin_form->login)));
	cJSON *jlogin_new = cJSON_CreateString((char *)gtk_entry_get_text(GTK_ENTRY(gui->profile_form->entry_login)));

	cJSON_AddItemToObject(jobj, "profile", profile);
	cJSON_AddItemToObject(jobj, "type", cJSON_CreateString("change_login"));
	cJSON_AddItemToObject(profile, "curr_user_login", jlogin_old);
	cJSON_AddItemToObject(profile, "new_user_login", jlogin_new);
	
	// cJSON_AddItemToObject(jobj, "pass", jpassword);
	jdata = cJSON_Print(jobj);
	write(gui->socketfd, jdata, strlen(jdata));
	cJSON_Delete(jobj);
	free(jdata);
	
    read(gui->socketfd, &status, 4);
    if (status == ST_UNCHANGE_LOGIN)
    	show_dialog(GTK_WIDGET(gui->profile_form->w_profile), "Changing login fail!");
    else if (status == ST_CHANGE_LOGIN)
    	show_dialog(GTK_WIDGET(gui->profile_form->w_profile), "Changing login complete!");
}
