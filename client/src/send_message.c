#include "client.h"

static char *curr_time(void) {
  time_t rawtime;
  struct tm * timeinfo;

  time (&rawtime);
  timeinfo = localtime ( &rawtime );
  return asctime(timeinfo);
}

static gint scroll(gpointer data) {
    t_gtk_components *gui = (t_gtk_components *)data;
    GtkScrolledWindow *window = GTK_SCROLLED_WINDOW(gui->chat_form->s_w_messages);
    GtkAdjustment *ad = gtk_scrolled_window_get_vadjustment(window);
    double l_pos = gtk_adjustment_get_upper(ad) + gtk_adjustment_get_page_increment(ad);

    gtk_adjustment_set_value(ad, l_pos);
    return false;
}

static void params(GtkWidget *text, GtkWidget *sender, GtkWidget *align, GtkWidget *time) {
    gtk_label_set_line_wrap(GTK_LABEL(text), TRUE);
    gtk_label_set_selectable(GTK_LABEL(text), TRUE);
    gtk_widget_set_name(sender, "user_name_label");
    gtk_widget_set_name(time, "current_time");
    gtk_widget_set_halign(sender, GTK_ALIGN_END);
    gtk_widget_set_valign(sender, GTK_ALIGN_START);
    gtk_widget_set_halign(time, GTK_ALIGN_END);
    gtk_widget_set_valign(time, GTK_ALIGN_START);
    gtk_widget_set_halign(text, GTK_ALIGN_END);
    gtk_widget_set_hexpand(align, TRUE);
}

static void printer(GtkWidget *list, const char *message, const char *name) {
	GtkWidget *text = gtk_label_new(message);
	GtkWidget *align = gtk_label_new("");
	GtkWidget *sender = gtk_label_new(name);
	char *time = curr_time();
    GtkWidget *time_label = gtk_label_new(time);
	GtkWidget *grid_box = gtk_grid_new();
	GtkWidget *grid = gtk_grid_new();

	params(text, sender, align, time_label);
    gtk_grid_insert_row(GTK_GRID(grid_box), 0);
    gtk_grid_insert_row(GTK_GRID(grid_box), 1);
    gtk_widget_set_hexpand(grid_box, FALSE);
    gtk_grid_insert_column(GTK_GRID(grid), 0);
    gtk_grid_insert_column(GTK_GRID(grid), 1);
    gtk_grid_attach(GTK_GRID(grid_box), sender, 0, 0, 1, 2);
    gtk_grid_attach(GTK_GRID(grid_box), text, 0, 1, 1, 2);
    gtk_grid_attach(GTK_GRID(grid), align, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), grid_box, 1, 0, 1, 1);
    gtk_list_box_insert(GTK_LIST_BOX(list), grid, -1);
    gtk_widget_show_all(list);
}



static char *cat_message(char *message) {
    char *res = NULL;
    int count_space = strlen(message) / 70;
    int count = 0;

    if (count_space == 0)
        return message;
    if (strlen(message) < 70)
        return message;
    res = mx_strnew(strlen(message) + count_space);
    for (int i = 0; message[i]; i++) {
        if (i % 70 == 0 && i != 0 && message[i] != ' ') {
            res[count] = ' ';
            count++;
        }
        res[count] = message[i];
        count++;
    }
    return res;
}

static void display_message(t_gtk_components *gui, char *login, char *message) {
    printer(gui->chat_form->list_messages, (const char *)message, (const char *)login);
    gtk_entry_set_text(GTK_ENTRY(gui->chat_form->entry_message), "");
    g_timeout_add(10, scroll, gui);
}

void send_message(GtkButton *button, gpointer data) {
	t_gtk_components *gui = (t_gtk_components *)data;
	(void)button;
	char *login = (char *)gtk_entry_get_text(GTK_ENTRY(gui->signin_form->login));
	char *message = (char *)gtk_entry_get_text(GTK_ENTRY(gui->chat_form->entry_message));
	char *jdata = NULL;
	int status = 0;

	cJSON *jobj = cJSON_CreateObject();
	cJSON *root_message = cJSON_CreateObject();
	cJSON_AddItemToObject(jobj, "message", root_message);
	cJSON_AddItemToObject(jobj, "type", cJSON_CreateString("save_message"));
	cJSON_AddItemToObject(root_message, "user_login", cJSON_CreateString(login));
	cJSON_AddItemToObject(root_message, "message", cJSON_CreateString(message));
	jdata = cJSON_Print(jobj);
	cJSON_Delete(jobj);
	if (strlen(message) > 300) {
       	show_dialog(gui->chat_form->w_chat, "Brevity is the soul of wit! Please shortening your messege!");
       	return;
    }
    else if (strlen(message) < 1) {
        show_dialog(gui->chat_form->w_chat, "Too short!");
        return;
    }
    else {
    	message = cat_message(message);
		if (message && strcmp(message, "")) {
			write(gui->socketfd, jdata, strlen(jdata));
			display_message(gui, login, message);
		}
		read(gui->socketfd, &status, 4);
	
		if (status == ST_UNSAVE_MSSG)
			show_dialog(GTK_WIDGET(gui->signup_form->w_signup), "Save message failed!");
		else if (status == ST_SAVE_MSSG)
			printf("%s\n", "spasi i sohrani!");
	}
}
