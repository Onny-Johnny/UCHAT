#include "client.h"

void open_window(GtkButton *button, gpointer data) {
	GtkWidget *open = (GtkWidget *)data;
    (void)button;

    gtk_widget_show_all(open);
}
