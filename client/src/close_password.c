#include "client.h"

void close_password(GtkButton *button, gpointer data) {
	t_gtk_components *gui = (t_gtk_components *)data;
	(void)button;

    gtk_widget_hide(gui->profile_form->w_password);
    gtk_widget_show_all(gui->chat_form->w_chat);

}
