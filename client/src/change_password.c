#include "client.h"

static t_change_pass *change_pss(t_gtk_components *gui) {
	t_change_pass *ch_pss = (t_change_pass *)malloc(sizeof(t_change_pass));

	ch_pss->password = (char *)gtk_entry_get_text(GTK_ENTRY(gui->profile_form->entry_oldpass));
	ch_pss->new_pass = (char *)gtk_entry_get_text(GTK_ENTRY(gui->profile_form->entry_newpass));
	ch_pss->conf_new_pass = (char *)gtk_entry_get_text(GTK_ENTRY(gui->profile_form->entry_newpass2));
	return ch_pss;
}


void change_password(GtkButton *button, gpointer data) {
	(void)button;
	t_gtk_components *gui = (t_gtk_components *)data;
	char *jdata = NULL;
	t_change_pass *changer = change_pss(gui);
	int status = 0;

	if (!strcmp(changer->new_pass, changer->conf_new_pass)
		&& check_data(changer->new_pass) && check_data(changer->conf_new_pass)) {
		cJSON *jobj = cJSON_CreateObject();
		cJSON *password = cJSON_CreateObject();
		cJSON *jpass_old = cJSON_CreateString(hash((char *)gtk_entry_get_text(GTK_ENTRY(gui->profile_form->entry_oldpass)), gui->key));
		cJSON *jpass_new = cJSON_CreateString(hash((char *)gtk_entry_get_text(GTK_ENTRY(gui->profile_form->entry_newpass2)), gui->key));
	
		cJSON_AddItemToObject(jobj, "pass", password);
		cJSON_AddItemToObject(jobj, "type", cJSON_CreateString("change_pass"));
		cJSON_AddItemToObject(password, "curr_user_pass", jpass_old);
		cJSON_AddItemToObject(password, "new_user_pass", jpass_new);
		jdata = cJSON_Print(jobj);

		write(gui->socketfd, jdata, strlen(jdata));
		cJSON_Delete(jobj);
		free(jdata);
	}
	else if (!check_data(changer->new_pass) || !check_data(changer->conf_new_pass))
		show_dialog(gui->profile_form->w_password, "Incorrect password!\n");
	else if (strcmp(changer->new_pass, changer->conf_new_pass))
		show_dialog(gui->profile_form->w_password, "Password mismatch!\n");
	read(gui->socketfd, &status, 4);
	if (status == ST_UNCHANGE_PASS)
		show_dialog(GTK_WIDGET(gui->profile_form->w_password), "Changing password fail!");
	else if (status == ST_CHANGE_PASS)
		show_dialog(GTK_WIDGET(gui->profile_form->w_password), "Changing password complete!");
	free(changer);
}
