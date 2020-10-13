#include "client.h"

void fill_chatform(t_w_chat *chat) {
	chat->chat_builder = gtk_builder_new_from_file(MX_WINDOW_CHAT);
	chat->w_chat = GTK_WIDGET(gtk_builder_get_object(chat->chat_builder, "window.chat"));
	chat->img_button_stickers = GTK_WIDGET(gtk_builder_get_object(chat->chat_builder, "image.button.stickers"));
	chat->button_profile = GTK_WIDGET(gtk_builder_get_object(chat->chat_builder, "button.profile"));
	chat->image_button_profile = GTK_WIDGET(gtk_builder_get_object(chat->chat_builder, "image.button.profile"));
	chat->button_setting = GTK_WIDGET(gtk_builder_get_object(chat->chat_builder, "button.setting"));
	chat->image_button_settings = GTK_WIDGET(gtk_builder_get_object(chat->chat_builder, "image.button.settings"));
	chat->button_logout = GTK_WIDGET(gtk_builder_get_object(chat->chat_builder, "button.logout"));
	chat->image_button_logout = GTK_WIDGET(gtk_builder_get_object(chat->chat_builder, "image.button.logout"));
	chat->list_chats = GTK_WIDGET(gtk_builder_get_object(chat->chat_builder, "list.chats"));
	chat->box_control_pad = GTK_WIDGET(gtk_builder_get_object(chat->chat_builder, "image.button.group"));
	chat->list_chats = GTK_WIDGET(gtk_builder_get_object(chat->chat_builder, "list.chats"));
	chat->box_control_pad = GTK_WIDGET(gtk_builder_get_object(chat->chat_builder, "box.control.pad"));
	chat->s_w_messages = GTK_WIDGET(gtk_builder_get_object(chat->chat_builder, "s.w.messages"));
	chat->list_messages = GTK_WIDGET(gtk_builder_get_object(chat->chat_builder, "list.messages"));
	chat->send = GTK_WIDGET(gtk_builder_get_object(chat->chat_builder, "button.send"));
	chat->img_send = GTK_WIDGET(gtk_builder_get_object(chat->chat_builder, "image.button.send"));
	chat->entry_message = GTK_WIDGET(gtk_builder_get_object(chat->chat_builder, "entry.message"));
	chat->upload_file = GTK_WIDGET(gtk_builder_get_object(chat->chat_builder, "button.upload.file"));
	chat->img_upload = GTK_WIDGET(gtk_builder_get_object(chat->chat_builder, "image.button.upload"));
	chat->edit = GTK_WIDGET(gtk_builder_get_object(chat->chat_builder, "button.edit"));
	chat->img_edit = GTK_WIDGET(gtk_builder_get_object(chat->chat_builder, "image.button.edit"));
	chat->stickers = GTK_WIDGET(gtk_builder_get_object(chat->chat_builder, "button.stickers"));
}
