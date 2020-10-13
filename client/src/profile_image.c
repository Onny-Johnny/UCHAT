#include "client.h"

char *open_file_choose(GtkWindow *parent) {
    char *result_str = NULL;
    gint res = 0;
    GtkWidget *dialog = gtk_file_chooser_dialog_new(
        "Choose a file for upload!",
        parent,
        GTK_FILE_CHOOSER_ACTION_OPEN,
        "Open",
        GTK_RESPONSE_ACCEPT,
        NULL
    );

    g_signal_connect(dialog, "destroy", G_CALLBACK(gtk_widget_destroy), dialog);
    res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_ACCEPT) {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        char *filename = gtk_file_chooser_get_filename(chooser);

        result_str = strdup(filename);
        g_free(filename);
    }
    gtk_widget_destroy(dialog);
    return result_str;
}

void rep_img(GtkWidget *image, const char *filename, int w, int h) {
    GdkPixbuf *pxbscaled;
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(filename, NULL);

    if (pixbuf) {
        pxbscaled = gdk_pixbuf_scale_simple(pixbuf, w, h, GDK_INTERP_BILINEAR);
        gtk_image_set_from_pixbuf(GTK_IMAGE(image), pxbscaled);
        g_object_unref(pxbscaled);
        g_object_unref(pixbuf);
    }
}

void set_profile_img(GtkButton *button, gpointer data) {
    t_gtk_components *gui = (t_gtk_components *)data;
    char *group_img = open_file_choose(GTK_WINDOW(gui->profile_form->w_profile));
    char *login = (char *)gtk_entry_get_text(GTK_ENTRY(gui->signin_form->login));
    rep_img(gui->profile_form->img_avatar, group_img, 225, 225);

    GList *head = gtk_container_get_children(GTK_CONTAINER(gui->chat_form->list_chats));
    GList *node = head;

    while (node) {
        GtkWidget *grid = gtk_bin_get_child(GTK_BIN(node->data));
        GtkWidget *label = gtk_grid_get_child_at(GTK_GRID(grid), 1, 0);
        GtkWidget *img = gtk_grid_get_child_at(GTK_GRID(grid), 0, 0);
        if (!strcmp(login, gtk_label_get_text(GTK_LABEL(label))))
            rep_img(img, group_img, 48, 48);

        node = g_list_next(node);
    }
    g_list_free(head);
    (void)button;
}
