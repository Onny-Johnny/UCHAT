#include "client.h"

void clear_container(GtkWidget *con) {
    GList *head = gtk_container_get_children(GTK_CONTAINER(con));
    GList *node = head;

    while (node) {
        gtk_widget_destroy(GTK_WIDGET(node->data));
        node = g_list_next(node);
    }
    g_list_free(head);
}

static gint editor_upd_lst(gpointer data) {
    t_gtk_components *gui = (t_gtk_components *)data;
    char num_buf[5] = {0};

    clear_container(gui->edit_form->lines_count);
    for (int i = 0; i < 150; i++) {
        memset(num_buf, 0, 4);
        GtkWidget *num = gtk_label_new(num_buf);
        gtk_list_box_insert(GTK_LIST_BOX(gui->edit_form->lines_count), num, -1);
    }
    return 128;
}

void open_editor(GtkButton *button, gpointer data) {
    t_gtk_components *gui = (t_gtk_components *)data;
    (void)button;

    const gchar *text = gtk_entry_get_text(GTK_ENTRY(gui->chat_form->entry_message));
    GtkTextBuffer *b = gtk_text_view_get_buffer(GTK_TEXT_VIEW(gui->edit_form->tv_editor));

    gtk_text_buffer_set_text(b, text, 0);
    gtk_text_view_set_buffer(GTK_TEXT_VIEW(gui->edit_form->tv_editor), b);
    gui->f = editor_upd_lst(gui);
    gtk_window_get_position(GTK_WINDOW(gui->chat_form->w_chat), &(gui->w_x), &(gui->w_y));
    gtk_widget_hide(gui->chat_form->w_chat);
    gtk_widget_show_all(gui->edit_form->w_edit);
    gtk_window_move(GTK_WINDOW(gui->edit_form->w_edit), gui->w_x, gui->w_y + 22);
}
