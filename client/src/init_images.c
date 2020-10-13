#include "client.h"

void init_images(t_gtk_components *gui) {
    render_img(gui->chat_form->image_button_profile, MX_BUTTON_PROFILE, 45, 45);
    render_img(gui->chat_form->image_button_settings, MX_BUTTON_SETTINGS, 45, 45);
    render_img(gui->chat_form->image_button_logout, MX_BUTTON_LOGOUT, 45, 45);
    render_img(gui->chat_form->img_button_stickers, MX_BUTTON_EMOJI, 45, 45);
    render_img(gui->chat_form->img_send, MX_BUTTON_SEND, 45, 45);
    render_img(gui->profile_form->img_find_img, MX_BUTTON_FIND_IMG, 45, 45);
    render_img(gui->profile_form->img_avatar, MX_BUTTON_AVATAR, 45, 45);
    render_img(gui->chat_form->img_edit, MX_BUTTON_EDIT, 45, 45);
    render_img(gui->chat_form->img_upload, MX_BUTTON_UPLOAD, 45, 45);
}
