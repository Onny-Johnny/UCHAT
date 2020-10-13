#include "client.h"

void fill_profileform(t_w_profile *profile) {
	profile->profile_builder = gtk_builder_new_from_file(MX_WINDOW_PROFILE);
	profile->w_password = GTK_WIDGET(gtk_builder_get_object(profile->profile_builder, "window.password"));
	profile->password_close = GTK_WIDGET(gtk_builder_get_object(profile->profile_builder, "button.password.close"));
	profile->entry_newpass = GTK_WIDGET(gtk_builder_get_object(profile->profile_builder, "entry.newpass1"));
	profile->aply_password = GTK_WIDGET(gtk_builder_get_object(profile->profile_builder, "button.password.apply"));
	profile->entry_newpass2 = GTK_WIDGET(gtk_builder_get_object(profile->profile_builder, "entry.newpass2"));
	profile->entry_oldpass = GTK_WIDGET(gtk_builder_get_object(profile->profile_builder, "entry.oldpass"));
	profile->w_profile = GTK_WIDGET(gtk_builder_get_object(profile->profile_builder, "window.profile"));
	profile->img_avatar = GTK_WIDGET(gtk_builder_get_object(profile->profile_builder, "image.avatar"));
	profile->find_img = GTK_WIDGET(gtk_builder_get_object(profile->profile_builder, "button.find.image"));
	profile->img_find_img = GTK_WIDGET(gtk_builder_get_object(profile->profile_builder, "image.button.find.image"));
	profile->entry_login = GTK_WIDGET(gtk_builder_get_object(profile->profile_builder, "entry.login"));
	profile->close = GTK_WIDGET(gtk_builder_get_object(profile->profile_builder, "button.close"));
	profile->apply = GTK_WIDGET(gtk_builder_get_object(profile->profile_builder, "button.apply"));
	profile->password = GTK_WIDGET(gtk_builder_get_object(profile->profile_builder, "button.password"));
}
