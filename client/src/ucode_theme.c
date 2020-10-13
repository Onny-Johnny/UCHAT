#include "client.h"

void ucode_theme(GtkButton *button, gpointer data) {
	t_gtk_components *gui = (t_gtk_components *)data;
	(void)button;

	gtk_css_provider_load_from_path(gui->css_provider, MX_DARK_THEME, NULL);
}
