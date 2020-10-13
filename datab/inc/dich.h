#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "../../lib/cjson/inc/cJSON.h"

#define DB_NAME "dich.db"
#define ST_UNREG_USER 0
#define ST_REG_USER 1
#define ST_UNLOG_USER 2
#define ST_LOG_USER 3
#define ST_UNSAVE_MSSG 4
#define ST_SAVE_MSSG 5
#define ST_UNCHANGE_LOGIN 6
#define ST_CHANGE_LOGIN 7
#define ST_UNCHANGE_PASS 8
#define ST_CHANGE_PASS 9

typedef struct s_db_user t_db_user;
typedef struct s_db_message t_db_message;

struct s_db_user {
    int user_id;
    char *login;
    char *pass;
    char *token;
    char *type;
};

struct s_db_message {
    char *user_login;
    char *date;
    char *message;
    char *type;
};



sqlite3* connect_db(sqlite3 *db);
void create_table_db(sqlite3 *db);
int insert_into_users(sqlite3 *db, t_db_user *user);
int insert_into_messages(sqlite3 *db, t_db_message *message);
void select_from_db(sqlite3 *db, char *data, char *table);
int update_set_string_where_string_db(sqlite3 *db, char *table, char *column, char *data, char *where, char *whereData);
void update_set_int_where_string_db(sqlite3 *db, char *table, char *column, char *data, char *where, char *whereData);
void update_set_string_where_int_db(sqlite3 *db, char *table, char *column, char *data, char *where, char *whereData);
void update_set_int_where_int_db(sqlite3 *db, char *table, char *column, char *data, char *where, char *whereData);
void delete_from_table_where_int_db(sqlite3 *db, char *table, char *where, char *whereData);
void delete_from_table_where_string_db(sqlite3 *db, char *table, char *where, char *whereData);
t_db_user *mx_create_user(char *login, char *pass);
t_db_message *mx_create_message(char *user_login, char *message);
void print_table_json(cJSON *root);
void sql_to_json(sqlite3 *db, char *data, char *table);
void json_to_sql_insert_user(sqlite3 *db, cJSON *root);
t_db_user *json_to_user(cJSON *root);
t_db_message *json_to_message(cJSON *root);
cJSON *message_to_json(t_db_message *t_message);
int registration_user(sqlite3 *db, cJSON *root);
int login_user(sqlite3 *db, cJSON *root);
int save_message(sqlite3 *db, cJSON *root);
void send_messages_to_client(sqlite3 *db);
int update_set_string_where_string_db_pass(sqlite3 *db, char *table, char *column, char *data, char *where, char *whereData);
