#include "client.h"

void open_signupform(GtkButton *button, gpointer data) {
	t_gtk_components *gui = (t_gtk_components *)data;
	(void)button;

	//gtk_window_get_position(GTK_WINDOW(gui->signin_form->w_signin), &(gui->w_x), &(gui->w_y));
    gtk_widget_hide(gui->signin_form->w_signin);
    gtk_widget_show_all(gui->signup_form->w_signup);
    //gtk_window_move(GTK_WINDOW(gui->signup_form->w_signup), gui->w_x, gui->w_y + 22);

    gtk_entry_set_text(GTK_ENTRY(gui->signup_form->sgn_login), "");
    gtk_entry_set_text(GTK_ENTRY(gui->signup_form->sgn_password), "");
    gtk_entry_set_text(GTK_ENTRY(gui->signup_form->confirm_password), "");
}
