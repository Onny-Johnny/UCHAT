#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <time.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <glib-object.h>
//#include <openssl/evp.h>
//#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <openssl/ssl.h>

#include "../../server/inc/server.h"
#include "../../lib/cjson/inc/cJSON.h"

#include <ctype.h>
#include <sys/stat.h>
#include <pthread.h>

#define MX_WINDOW_LOGIN "client/glade/window.login.glade"
#define MX_WINDOW_SIGNUP "client/glade/window.signup.glade"
#define MX_WINDOW_CHAT "client/glade/chat.window.glade"
#define MX_WINDOW_PROFILE "client/glade/window.profile.glade"
#define MX_WINDOW_EDIT "client/glade/window.edit.glade"

#define MX_FT_THEME "client/glade/ft.css"
#define MX_DARK_THEME "client/glade/dark.css"
#define MX_UCODE_THEME "client/glade/ucode/css"

#define MX_AVATAR_MIS "client/img/glasses.png"
#define MX_BUTTON_PROFILE "client/img/avatar.png"
#define MX_BUTTON_LOGOUT "client/img/logout.png"
#define MX_BUTTON_SETTINGS "client/img/setting.png"
#define MX_BUTTON_EMOJI "client/img/chat.png"
#define MX_BUTTON_SEND "client/img/paper-plane.png"
#define MX_BUTTON_RESET "client/img/logout.png"
#define MX_BUTTON_EDIT "client/img/edit.png"
#define MX_BUTTON_APPLY "client/img/next.png"
#define MX_BUTTON_FIND_IMG "client/img/find.png"
#define MX_BUTTON_AVATAR "client/img/avatar-1.png"
#define MX_BUTTON_UPLOAD "client/img/upload.png"
#define MX_MAX_BUFF 1024

#define ST_UNREG_USER 0
#define ST_REG_USER 1
#define ST_UNLOG_USER 2
#define ST_LOG_USER 3
#define ST_UNSAVE_MSSG 4
#define ST_SAVE_MSSG 5
#define ST_UNCHANGE_LOGIN 6
#define ST_CHANGE_LOGIN 7


typedef struct      s_w_signin {
    GtkWidget       *w_signin;
    GtkWidget       *login;
    GtkWidget       *password;
    GtkWidget       *signin;
    GtkWidget       *signup;
    GtkWidget       *setting_button;
    GtkBuilder      *login_builder;
}                   t_w_signin;

typedef struct      s_w_settings {
    GtkWidget       *w_setting;
    GtkWidget       *dark;
    GtkWidget       *light;
    GtkWidget       *close;
}                   t_w_settings;

typedef struct      s_w_signup {
    GtkWidget       *w_signup;
    GtkWidget       *sgn_signup;
    GtkWidget       *sgn_login;
    GtkWidget       *sgn_password;
    GtkWidget       *confirm_password;
    GtkBuilder      *signup_builder;
}                   t_w_signup;

typedef struct      s_chat_add {
    char            *reciver;
    char            *contact;
}                   t_chat_add;

typedef struct      s_w_profile {
    GtkWidget       *w_password;
    GtkWidget       *password_close;
    GtkWidget       *entry_newpass;
    GtkWidget       *aply_password;
    GtkWidget       *entry_newpass2;
    GtkWidget       *entry_oldpass;
    GtkWidget       *w_profile;
    GtkWidget       *img_avatar;
    GtkWidget       *find_img;
    GtkWidget       *img_find_img;
    GtkWidget       *entry_login;
    GtkWidget       *close;
    GtkWidget       *apply;
    GtkWidget       *password;
    GtkBuilder      *profile_builder;
}                   t_w_profile;

typedef struct      s_w_chat {
    GtkWidget       *w_chat;
    GtkWidget       *img_button_stickers;
    GtkWidget       *button_profile;
    GtkWidget       *image_button_profile;
    GtkWidget       *image_button_settings;
    GtkWidget       *button_logout;
    GtkWidget       *image_button_logout;
    GtkWidget       *list_chats;
    GtkWidget       *box_control_pad;
    GtkWidget       *s_w_messages;
    GtkWidget       *list_messages;
    GtkWidget       *send;
    GtkWidget       *img_send;
    GtkWidget       *entry_message;
    GtkWidget       *upload_file;
    GtkWidget       *img_upload;
    GtkWidget       *edit;
    GtkWidget       *img_edit;
    GtkWidget       *stickers;
    GtkBuilder      *chat_builder;
    GtkWidget       *button_setting;
}                   t_w_chat;

typedef struct      s_w_edit {
    GtkBuilder      *edit_builder;
    GtkWidget       *w_edit;
    GtkWidget       *lines_count;
    GtkWidget       *tv_editor;
    GtkWidget       *ed_apply;
    GtkWidget       *img_ed_apply;
}                   t_w_editor;

typedef struct  	s_gtk_components {
	int 			socketfd;
	// Window position
    gint 			w_x;
    gint 			w_y;
    GdkPixbuf 		*icon;
    // Application
    GtkCssProvider 	*css_provider;
    //window
    t_w_signin 		*signin_form;
    t_w_settings 	*setting_form;
    t_w_signup      *signup_form;
    t_w_chat        *chat_form;
    t_chat_add      *chat_add;
    t_w_profile     *profile_form;
    t_w_editor      *edit_form;

    char 			buff[MX_MAX_BUFF];
    char 			*data_recv;
    gint            f;

    char            *key;

}					t_gtk_components;

typedef struct      s_registration {
    char            *reg_login;
    char            *reg_password;
    char            *reg_conf_password;
}                   t_registration;

typedef struct      s_change_pass {
    char            *password;
    char            *new_pass;
    char            *conf_new_pass;
}                   t_change_pass;

void *listening_thread(void *arg);
void error_msg(char *msg);
void error(char *msg);
void *client_func(void *data);
void init_app(int argc, char **argv, int socket);
void resize_warning(GtkWindow *window, GdkEventWindowState *event, gpointer data);
void build_login(GtkBuilder *builder);
void build_signup(GtkBuilder *builder);
void client_logged_in(GtkButton *butt, gpointer data);
void open_window(GtkButton *button, gpointer data);
void connect_signals(t_gtk_components *gui);
void fill_chatform(t_w_chat *chat);
void ft_theme(GtkButton *button, gpointer data);
void client_registration(GtkButton *button, gpointer data);
void mx_close_signup(GtkButton *button, gpointer data);
void close_window(GtkButton *button, gpointer data);
char *init_salt(unsigned char *hash);
// char *hash(char *pass);
void show_dialog(GtkWidget *parent, char *message);
void ucode_theme(GtkButton *button, gpointer data);
bool check_data(char *data);
void open_signupform(GtkButton *button, gpointer data);
void send_message(GtkButton *button, gpointer data);
void profile(GtkButton *button, gpointer data);
char *mx_strnew(const int size);
void fill_profileform(t_w_profile *profile);
void open_settings(GtkButton *button, gpointer data);
void change_login(GtkButton *button, gpointer data);
void open_wchange_password(GtkButton *button, gpointer data);
// void close_setting(GtkButton *button, gpointer data);
void close_password(GtkButton *button, gpointer data);
void change_password(GtkButton *button, gpointer data);
char *mx_open_file_chooser(GtkWindow *parent);
void rep_img(GtkWidget *image, const char *filename, int w, int h);
void set_profile_img(GtkButton *button, gpointer data);
void close_profile(GtkButton *button, gpointer data);
void client_logout(GtkButton *button, gpointer data);
char *open_file_choose(GtkWindow *parent);
void clear_container(GtkWidget *con);
void fill_editform(t_w_editor *edit);
void open_editor(GtkButton *button, gpointer data);
void apply_edit(GtkButton *button, gpointer data);
char *hash(char *pass, char *key);
void init_images(t_gtk_components *gui);
void render_img(GtkWidget *image, const char *filename, int w, int h);

#endif
