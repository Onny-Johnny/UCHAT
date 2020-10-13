#include "client.h"

void resize_warning(GtkWindow *window, GdkEventWindowState *event, gpointer data) {
	(void)window;
	(void)data;

	// GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
	// GtkWidget *dialog = gtk_message_dialog_new(
 //        				GTK_WINDOW(GTK_WIDGET(window)),
 //        				flags,
 //        				GTK_MESSAGE_WARNING,
 //        				GTK_BUTTONS_OK,
 //        				"\n%s",
 //        				"Maximizing window not awailable");
	if (event->new_window_state & GDK_WINDOW_STATE_MAXIMIZED) {
        gtk_window_unmaximize(window);
     //    gtk_dialog_run(GTK_DIALOG(dialog));
    	// gtk_widget_destroy(dialog);
        show_dialog(GTK_WIDGET(window), "No you can't:)");
    }
}
