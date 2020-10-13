#include "client.h"

void apply_edit(GtkButton *button, gpointer data) {
    t_gtk_components *gui = (t_gtk_components *)data;
	(void)button;
    GtkTextIter start;
    GtkTextIter end;
    GtkTextBuffer *b = gtk_text_view_get_buffer(GTK_TEXT_VIEW(gui->edit_form->tv_editor));
    const gchar *text;

    gtk_text_buffer_get_bounds(b, &start, &end);
    text = gtk_text_buffer_get_text(b, &start, &end, FALSE);
    gtk_entry_set_text(GTK_ENTRY(gui->chat_form->entry_message), text);
    gtk_window_get_position(GTK_WINDOW(gui->edit_form->w_edit), &(gui->w_x), &(gui->w_y));
    gtk_widget_hide(gui->edit_form->w_edit);
    gtk_widget_show_all(gui->chat_form->w_chat);
    gtk_widget_hide(gui->chat_form->upload_file);
    // gtk_window_move(GTK_WINDOW(gui->chat_form->w_chat), gui->w_x, gui->w_y + 22);
}
