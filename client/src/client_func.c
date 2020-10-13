#include "client.h"

// static gboolean reconnect(void *data) {
// 	t_gtk_components *gui = (t_gtk_components *)data;

// 	show_dialog(gui->chat_form->w_chat, "Kurillka close in 3,2,1,0");
// 	return 0;
// }

// void *client_func(void *data) {
// 	t_gtk_components *gui = (t_gtk_components *)data;
// 	// cJSON *jobj;
// 	int status = 0;

// 	while(1) {
// 		bzero(gui->buff, sizeof(gui->buff));
// 		if (read(gui->socketfd, &status, 10) < 0) {
// 			gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, reconnect, gui, 0);
//             sleep(3);
//             exit(0);
// 		}
// 		if (status == ST_UNREG_USER)
// 			show_dialog(GTK_WIDGET(gui->signup_form->w_signup), "Registration failed!");
// 		else if (status == ST_REG_USER) {
// 			show_dialog(GTK_WIDGET(gui->signup_form->w_signup), "Registration success!");
// 			gtk_widget_hide(gui->signup_form->w_signup);
//     		gtk_widget_show_all(gui->signin_form->w_signin);
//     	}
//     	else if (status == ST_UNLOG_USER)
//     		show_dialog(GTK_WIDGET(gui->signup_form->w_signup), "Login failed!");
//     	else if (status == ST_LOG_USER) {
// 			gtk_widget_hide(gui->signin_form->w_signin);
//     		gtk_widget_show_all(gui->chat_form->w_chat);    		
//     	}
//     	else if (status == ST_UNSAVE_MSSG)
//     		show_dialog(GTK_WIDGET(gui->signup_form->w_signup), "Save message failed!");
//     	else if (status == ST_SAVE_MSSG)
//     		printf("%s", "messege save");
//     	//
// 	}
// 	return NULL;
// }
