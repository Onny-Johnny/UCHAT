#include "client.h"

void close_window(GtkButton *button, gpointer data) {
	GtkWidget *close = (GtkWidget *)data;
    (void)button;

    gtk_widget_hide(close);
}
