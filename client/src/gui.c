#include "client.h"

static void fill_signinform(t_w_signin *login_form) {
	login_form->login_builder = gtk_builder_new_from_file(MX_WINDOW_LOGIN);
	login_form->w_signin = GTK_WIDGET(gtk_builder_get_object(login_form->login_builder, "window.login"));
	login_form->login = GTK_WIDGET(gtk_builder_get_object(login_form->login_builder, "entry.login"));
	login_form->password = GTK_WIDGET(gtk_builder_get_object(login_form->login_builder, "entry.password"));
	login_form->signin = GTK_WIDGET(gtk_builder_get_object(login_form->login_builder, "button.signin"));
	login_form->signup = GTK_WIDGET(gtk_builder_get_object(login_form->login_builder, "button.signup"));
	login_form->setting_button = GTK_WIDGET(gtk_builder_get_object(login_form->login_builder, "button.settings"));
}

static void fill_settingform(GtkBuilder *builder, t_w_settings *setting_form) {
	setting_form->w_setting = GTK_WIDGET(gtk_builder_get_object(builder, "window.settings"));
	setting_form->dark = GTK_WIDGET(gtk_builder_get_object(builder, "button.theme.dark"));
	setting_form->light = GTK_WIDGET(gtk_builder_get_object(builder, "button.theme.light"));
	setting_form->close = GTK_WIDGET(gtk_builder_get_object(builder, "button.close"));
}

static void fill_signupform(t_w_signup *signup_form) {
	signup_form->signup_builder = gtk_builder_new_from_file(MX_WINDOW_SIGNUP);
	signup_form->w_signup = GTK_WIDGET(gtk_builder_get_object(signup_form->signup_builder, "window.signup"));
	signup_form->sgn_signup = GTK_WIDGET(gtk_builder_get_object(signup_form->signup_builder, "button.signup"));
	signup_form->sgn_login = GTK_WIDGET(gtk_builder_get_object(signup_form->signup_builder, "entry.login"));
	signup_form->sgn_password = GTK_WIDGET(gtk_builder_get_object(signup_form->signup_builder, "entry.password"));
	signup_form->confirm_password = GTK_WIDGET(gtk_builder_get_object(signup_form->signup_builder, "entry.password2"));
}

static t_gtk_components *fill_components(int socket) {
	t_gtk_components *gui = (t_gtk_components *)malloc(sizeof(t_gtk_components));
	gui->socketfd = socket;
	gui->w_x = 0;
	gui->w_y = 0;
	gui->key = "asdqwezxc";

	gui->signin_form = (t_w_signin *)malloc(sizeof(t_w_signin));
	gui->setting_form = (t_w_settings *)malloc(sizeof(t_w_settings));
	gui->signup_form = (t_w_signup *)malloc(sizeof(t_w_signup));
	gui->chat_form = (t_w_chat *)malloc(sizeof(t_w_chat));
	gui->profile_form = (t_w_profile *)malloc(sizeof(t_w_profile));
	gui->edit_form = (t_w_editor *)malloc(sizeof(t_w_profile));
	fill_signinform(gui->signin_form);
 	fill_settingform(gui->signin_form->login_builder, gui->setting_form);
	fill_signupform(gui->signup_form);
	fill_chatform(gui->chat_form);
	fill_profileform(gui->profile_form);
	fill_editform(gui->edit_form);
	return gui;
}

void init_app(int argc, char **argv, int socket) {
	t_gtk_components *gui = NULL;
	// pthread_t c;

	gtk_init(&argc, &argv);
	gui = fill_components(socket);
	init_images(gui);
	gui->css_provider = gtk_css_provider_new();
	gtk_css_provider_load_from_path(gui->css_provider, MX_FT_THEME, NULL);

	GdkScreen * display = gdk_screen_get_default();
	gtk_style_context_add_provider_for_screen(display, GTK_STYLE_PROVIDER(gui->css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

	connect_signals(gui);
	gtk_widget_show_all(gui->signin_form->w_signin);
	// pthread_create(&c, NULL, client_func, (void *)&gui);
	gtk_main();
    free(gui);
}
