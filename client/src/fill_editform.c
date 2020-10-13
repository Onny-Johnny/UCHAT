#include "client.h"

void fill_editform(t_w_editor *edit) {
	edit->edit_builder = gtk_builder_new_from_file(MX_WINDOW_EDIT);
	edit->w_edit = GTK_WIDGET(gtk_builder_get_object(edit->edit_builder, "window.edit"));
	edit->lines_count = GTK_WIDGET(gtk_builder_get_object(edit->edit_builder, "list.lines.count"));
	edit->tv_editor = GTK_WIDGET(gtk_builder_get_object(edit->edit_builder, "tv.editor"));
	edit->ed_apply = GTK_WIDGET(gtk_builder_get_object(edit->edit_builder, "button.apply"));
	edit->img_ed_apply = GTK_WIDGET(gtk_builder_get_object(edit->edit_builder, "image.button.apply"));
}
