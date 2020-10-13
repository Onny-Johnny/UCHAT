#include "client.h"

void ft_theme(GtkButton *button, gpointer data) {
	t_gtk_components *gui = (t_gtk_components *)data;
	(void)button;

	gtk_css_provider_load_from_path(gui->css_provider, MX_FT_THEME, NULL);
}
