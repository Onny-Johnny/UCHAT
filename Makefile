CL_NAME	=	uchat
SV_NAME = 	uchat_server

CFLG	=	-std=c11 $(addprefix -W, all extra error pedantic) -g 
INCD = inc
CL_SRCD	=	client/src
SV_SRCD =	server/src
DB_SRCD =	datab/src
CL_INCD	=	client/inc
SV_INCD =	server/inc
DB_INCD =	datab/inc
CL_OBJD	=	client/obj
SV_OBJD =	server/obj
DB_OBJD =	datab/obj
CL_GTK_FLAGS = `pkg-config --cflags --libs gtk+-3.0`
CL_GTK_SORT_FLAGS = `pkg-config --cflags gtk+-3.0`
SQL_FLAGS = -lsqlite3
SANITAIZER_FLAGS =  -fsanitize=address
CL_THREADS_LINKER = -pthread -lpthread

LIBS		= cJSON.a
LIBS_INCS 	= cJSON.h
LIBS_INC	= lib/cjson/inc/cJSON.h

DB_MXD	=	datab
DB_MXA:=	$(DB_MXD)/dich_db
DB_MXI:=	$(DB_MXD)/$(INCD)

CL_INC		=	client.h
SV_INC		=	server.h

CL_INCS	=	$(addprefix $(CL_INCD)/, $(CL_INC))
SV_INCS =	$(addprefix $(SV_INCD)/, $(SV_INC))

CL_SRC		=	client.c \
				gui.c \
				signals.c \
				client_registration.c \
				close_window.c \
				fill_chatform.c \
				ft_theme.c \
				open_window.c \
				resize_warning.c \
				security.c \
				show_dialog.c \
				ucode_theme.c \
				client_logged_in.c \
				signup_form_open.c \
				profile.c \
				send_message.c \
				mx_strnew.c \
				fill_profileform.c \
				error.c \
				client_func.c \
				open_settings.c \
				change_login.c \
				open_wchange_password.c \
				change_password.c \
				close_password.c \
				client_logout.c \
				close_profile.c \
				profile_image.c \
				edit.c \
				fill_editform.c \
				apply_edit.c \
				hash.c \
				init_images.c \
				render_img.c \


SV_SRC		=	server.c \
				error.c \
				list.c \
				mx_create_log.c \
				mx_itoa.c \
				mx_strnew.c \
				server_loop.c \
				make_demon.c \




CL_SRCS	=	$(addprefix $(CL_SRCD)/, $(CL_SRC))
SV_SRCS =	$(addprefix $(SV_SRCD)/, $(SV_SRC))
CL_OBJS	=	$(addprefix $(CL_OBJD)/, $(CL_SRC:%.c=%.o))
SV_OBJS	=	$(addprefix $(SV_OBJD)/, $(SV_SRC:%.c=%.o))

all: install

$(FILE:a/%=%)

install: install_db $(DB_MXA) lib_install install_client install_server

install_db:
	@make -sC $(DB_MXD)

lib: lib_install
	@make -C lib/cjson uninstall

lib_install:
	@cp $(LIBS_INC) .
	@make -C lib/cjson install
	@cp lib/cjson/cJSON.a .
	
install_client: $(CL_NAME)

$(CL_NAME): $(CL_OBJS)
	@clang $(CFLG) $(CL_OBJS) $(CL_GTK_FLAGS) -L/usr/local/opt/openssl/lib/ -lssl -lcrypto -lmx -rdynamic -o $@ $(LIBS)
	@printf "\r\33[2K$@ \033[32;1mcreated\033[0m\n"

$(CL_OBJD)/%.o: $(CL_SRCD)/%.c $(CL_INCS)
	@clang $(CFLG) -c $< $(CL_GTK_SORT_FLAGS) -I/usr/local/opt/openssl/include/ -o $@ -I$(CL_INCD) 
	@printf "\r\33[2K$(CL_NAME) \033[33;1mcompile \033[0m$(<:$(CL_SRCD)/%.c=%) "

$(CL_OBJS): | $(CL_OBJD)

$(CL_OBJD):
	@mkdir -p $@

install_server: $(SV_NAME)

$(SV_NAME): $(SV_OBJS)
	@clang $(CFLG) $(SV_OBJS)  -L/usr/local/opt/openssl/lib/ -lssl -lcrypto -lmx -o $@ $(DB_MXA) -lsqlite3 $(LIBS)
	@printf "\r\33[2K$@ \033[32;1mcreated\033[0m\n"

$(SV_OBJD)/%.o: $(SV_SRCD)/%.c $(SV_INCS)
	@clang $(CFLG) -c $< -I/usr/local/opt/openssl/include/ -o $@ -I$(SV_INCD) -I$(DB_MXI)
	@printf "\r\33[2K$(SV_NAME) \033[33;1mcompile \033[0m$(<:$(SV_SRCD)/%.c=%) "

$(SV_OBJS): | $(SV_OBJD)

$(SV_OBJD):
	@mkdir -p $@

$(DB_MXA):
	@make -sC $(DB_MXD)

clean:
	@make -C lib/cjson uninstall
	@make -sC $(DB_MXD) $@
	@rm -rf $(CL_OBJD)
	@rm -rf $(SV_OBJD)
	@rm -rf $(DB_MXD)/$(DB_MXA)
	@printf "$(CL_OBJD)\t   \033[31;1mdeleted\033[0m\n"
	@printf "$(SV_OBJD)\t   \033[31;1mdeleted\033[0m\n"


uninstall: clean
	@rm -rf $(CL_NAME)
	@make -sC $(DB_MXD) $@
	@rm -rf $(SV_NAME)
	@printf "$(CL_NAME) \033[31;1muninstalled\033[0m\n"
	@printf "$(SV_NAME) \033[31;1muninstalled\033[0m\n"

uninstall_server:
	@make -sC $(DB_MXD) uninstall
	@rm -rf $(SV_NAME)
	@printf "$(SV_NAME) \033[31;1muninstalled\033[0m\n"

reinstall: uninstall install

reinstall_server : uninstall_server install_server
