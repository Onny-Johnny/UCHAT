#include "client.h"

void open_wchange_password(GtkButton *button, gpointer data) {
	t_gtk_components *gui = (t_gtk_components *)data;
	(void)button;

    gtk_widget_hide(gui->profile_form->w_profile);
    gtk_widget_show_all(gui->profile_form->w_password);
}
