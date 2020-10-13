#include "client.h"

void profile(GtkButton *button, gpointer data) {
	t_gtk_components *gui = (t_gtk_components *)data;
	(void)button;

    gtk_widget_hide(gui->chat_form->w_chat);
    gtk_widget_show_all(gui->profile_form->w_profile);
}
