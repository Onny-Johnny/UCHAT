#include "client.h"

static t_registration *fill_registration(t_w_signup *signup_form, char *key) {
	t_registration *signup_data = (t_registration *)malloc(sizeof(t_registration));

	signup_data->reg_login = (char *)gtk_entry_get_text(GTK_ENTRY(signup_form->sgn_login));
	signup_data->reg_password = hash((char *)gtk_entry_get_text(GTK_ENTRY(signup_form->sgn_password)), key);
	signup_data->reg_conf_password = hash((char *)gtk_entry_get_text(GTK_ENTRY(signup_form->confirm_password)), key);
	return signup_data;
}

bool check_data(char *data) {
	int i = 0;

	while (data[i]) {
		if (isalpha(data[i]) || isdigit(data[i]))
			return 1;
		i++;
	}
	return 0;
}

static void handler_errors(t_registration *reg, t_w_signup *signup) {
	if (!check_data(reg->reg_login))
		show_dialog(signup->w_signup, "Incorrect login.\n");
	if (!check_data(reg->reg_password))
		show_dialog(signup->w_signup, "Incorrect password.\n");
	if (strcmp(reg->reg_password, reg->reg_conf_password))
		show_dialog(signup->w_signup, "Passwords must be identical.\n");
}

static void get_json(cJSON *jobj, t_registration *reg) {
	cJSON *user = cJSON_CreateObject();
	cJSON_AddItemToObject(jobj, "user", user);
	cJSON_AddItemToObject(jobj, "type", cJSON_CreateString("reg_user"));
	cJSON_AddItemToObject(user, "login", cJSON_CreateString(reg->reg_login));
	cJSON_AddItemToObject(user, "pass", cJSON_CreateString(reg->reg_password));
}


void client_registration(GtkButton *button, gpointer data) {
	t_gtk_components *gui = (t_gtk_components *)data;
	t_registration *reg = fill_registration(gui->signup_form, gui->key);
	cJSON *jobj = cJSON_CreateObject();
	char *json_data = NULL;
	int status = 0;
	(void)button;

	handler_errors(reg, gui->signup_form);
	get_json(jobj, reg);
	json_data = cJSON_Print(jobj);
	write(gui->socketfd, json_data, strlen(json_data));
	cJSON_Delete(jobj);
	read(gui->socketfd, &status, 4);
	if (status == ST_UNREG_USER) {
		show_dialog(GTK_WIDGET(gui->signup_form->w_signup), "Registration failed!");
		gtk_widget_hide(gui->signup_form->w_signup);
    	gtk_widget_show_all(gui->signin_form->w_signin);
	}
	else if(status == ST_REG_USER) {
		show_dialog(GTK_WIDGET(gui->signup_form->w_signup), "Registration success!");
		gtk_widget_hide(gui->signup_form->w_signup);
    	gtk_widget_show_all(gui->signin_form->w_signin);
	}
    free(json_data);
}
