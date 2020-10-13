#include "client.h"

void open_settings(GtkButton *button, gpointer data) {
	t_gtk_components *gui = (t_gtk_components *)data;
	(void)button;

    // gtk_widget_hide(gui->chat_form->w_chat);
    gtk_widget_show_all(gui->setting_form->w_setting);
}
