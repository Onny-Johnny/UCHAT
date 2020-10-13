#include "client.h"

static void resize_form_signals(t_gtk_components *gui) {
	g_signal_connect(gui->signin_form->w_signin, "window-state-event", G_CALLBACK(resize_warning), gui->signin_form);
	g_signal_connect(gui->setting_form->w_setting, "window-state-event", G_CALLBACK(resize_warning), gui->setting_form);
	g_signal_connect(gui->signup_form->w_signup, "window-state-event", G_CALLBACK(resize_warning), gui->signup_form);
	g_signal_connect(gui->chat_form->w_chat, "window-state-event", G_CALLBACK(resize_warning), gui->chat_form);
	g_signal_connect(gui->profile_form->w_profile, "window-state-event", G_CALLBACK(resize_warning), gui->profile_form);
	g_signal_connect(gui->profile_form->w_password, "window-state-event", G_CALLBACK(resize_warning), gui->profile_form);
	g_signal_connect(gui->edit_form->w_edit, "window-state-event", G_CALLBACK(resize_warning), gui);
}

static void quit_signals(t_gtk_components *gui) {
	g_signal_connect(gui->signin_form->w_signin, "destroy", G_CALLBACK(exit), (void *)0);
	g_signal_connect(gui->setting_form->w_setting, "destroy", G_CALLBACK(exit), (void *)0);
	g_signal_connect(gui->signup_form->w_signup, "destroy", G_CALLBACK(exit), (void *)0);
	g_signal_connect(gui->chat_form->w_chat, "destroy", G_CALLBACK(exit), (void *)0);
	g_signal_connect(gui->profile_form->w_profile, "destroy", G_CALLBACK(exit), (void *)0);
	g_signal_connect(gui->profile_form->w_password, "destroy", G_CALLBACK(exit), (void *)0);
}

static void click_signals(t_gtk_components *gui) {
	g_signal_connect(gui->signin_form->signin, "clicked", G_CALLBACK(client_logged_in), gui);
	g_signal_connect(gui->signin_form->setting_button, "clicked", G_CALLBACK(open_window), gui->setting_form->w_setting);
	g_signal_connect(gui->setting_form->close, "clicked", G_CALLBACK(close_window), gui->setting_form->w_setting);
	g_signal_connect(gui->setting_form->light, "clicked", G_CALLBACK(ft_theme), gui);
	g_signal_connect(gui->setting_form->dark, "clicked", G_CALLBACK(ucode_theme), gui);
	g_signal_connect(gui->signin_form->signup, "clicked", G_CALLBACK(open_signupform), gui);
	g_signal_connect(gui->signup_form->sgn_signup, "clicked", G_CALLBACK(client_registration), gui);
}

static void chat_signals(t_gtk_components *gui) {
	g_signal_connect(gui->chat_form->send, "clicked", G_CALLBACK(send_message), gui);
	g_signal_connect(gui->chat_form->button_profile, "clicked", G_CALLBACK(profile), gui);
	g_signal_connect(gui->chat_form->button_setting, "clicked", G_CALLBACK(open_settings), gui);
	g_signal_connect(gui->chat_form->button_setting, "clicked", G_CALLBACK(open_settings), gui);

}

static void profile_signals(t_gtk_components *gui) {
	g_signal_connect(gui->profile_form->apply, "clicked", G_CALLBACK(change_login), gui);
	g_signal_connect(gui->profile_form->password, "clicked", G_CALLBACK(open_wchange_password), gui);
	g_signal_connect(gui->profile_form->aply_password, "clicked", G_CALLBACK(change_password), gui);
	g_signal_connect(gui->profile_form->password_close, "clicked", G_CALLBACK(close_password), gui);
	g_signal_connect(gui->profile_form->close, "clicked", G_CALLBACK(close_profile), gui);
	g_signal_connect(gui->chat_form->button_logout, "clicked", G_CALLBACK(client_logout), gui);
	g_signal_connect(gui->profile_form->find_img, "clicked", G_CALLBACK(set_profile_img), gui);
	
}

static void edit_signals(t_gtk_components *gui) {
	g_signal_connect(gui->chat_form->edit, "clicked", G_CALLBACK(open_editor), gui);
	g_signal_connect(gui->edit_form->ed_apply, "clicked", G_CALLBACK(apply_edit), gui);
}

void connect_signals(t_gtk_components *gui) {
	resize_form_signals(gui);
	quit_signals(gui);
	click_signals(gui);
	chat_signals(gui);
	profile_signals(gui);
	edit_signals(gui);
}
