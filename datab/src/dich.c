#include "../inc/dich.h"

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

sqlite3* connect_db(sqlite3 *db) {
	if (sqlite3_open(DB_NAME, &db)) {
		fprintf(stderr, "Ошибка открытия/создания БД: %s\n", sqlite3_errmsg(db));
	}
	return db;
}

void create_table_db(sqlite3 *db) {
	char *err = 0;
	char *SQL_users = "CREATE TABLE IF NOT EXISTS users ("
                           "id             INTEGER         PRIMARY KEY      NOT NULL,"
                           "login          VARCHAR(255)    UNIQUE           NOT NULL,"
                           "pass           TEXT                             NOT NULL,"
                           "token          TEXT                             NOT NULL);";

	if (sqlite3_exec(db, SQL_users, 0, 0, &err)) {
		fprintf(stderr, "Ошибка SQL: %s\n", err);
		sqlite3_free(err);
	}

	char *SQL_mesages = "CREATE TABLE IF NOT EXISTS messages ("
                           "id             INTEGER         PRIMARY KEY      NOT NULL,"
                           "user_login     VARCHAR(255)                     NOT NULL,"
                           "date           DATETIME                         NOT NULL,"
                           "message        TEXT                             NOT NULL);";

	if (sqlite3_exec(db, SQL_mesages, 0, 0, &err)) {
		fprintf(stderr, "Ошибка SQL: %s\n", err);
		sqlite3_free(err);
	}
}

int insert_into_users(sqlite3 *db, t_db_user *user) {
	sqlite3_stmt *stmt;
	int err = 0;

	err = sqlite3_prepare_v2(db, "INSERT INTO users (login, pass, token) "
							"VALUES (?1, ?2, ?3);",
                            -1, &stmt, NULL);

	if (err != SQLITE_OK) {
    	printf("prepare failed: %s\n", sqlite3_errmsg(db));
    	return ST_UNREG_USER;
	}

	sqlite3_bind_text(stmt, 1, user->login, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, user->pass, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, user->token, -1, SQLITE_STATIC);

    err = sqlite3_step(stmt);
	if (err != SQLITE_DONE) {
	    printf("execution failed: %s\n", sqlite3_errmsg(db));
	    sqlite3_finalize(stmt);
	    return ST_UNREG_USER;
	}
	sqlite3_finalize(stmt);
	fprintf(stdout, "Records created successfully\n");
	return ST_REG_USER;
}

int insert_into_messages(sqlite3 *db, t_db_message *message) {
	sqlite3_stmt *stmt;
	int err = 0;

	err = sqlite3_prepare_v2(db, "INSERT INTO messages (user_login, date, message) "
							"VALUES (?1, datetime('now', 'localtime'), ?2);",
                            -1, &stmt, NULL);

	if (err != SQLITE_OK) {
    	printf("prepare failed: %s\n", sqlite3_errmsg(db));
    	return ST_UNSAVE_MSSG;
	}

	sqlite3_bind_text(stmt, 1, message->user_login, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, message->message, -1, SQLITE_STATIC);

    err = sqlite3_step(stmt);
	if (err != SQLITE_DONE) {
	    printf("execution failed: %s\n", sqlite3_errmsg(db));
	    sqlite3_finalize(stmt);
	    return ST_UNSAVE_MSSG;
	}

	sqlite3_finalize(stmt);
	fprintf(stdout, "Records created successfully\n");
	return ST_SAVE_MSSG;
}

static int callback_print_select(void *data, int argc, char **argv, char **azColName) {
	fprintf(stderr, "%s: ", (const char *)data);

	for(int i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i]);
	}
	printf ("\n");
	return 0;
}

void select_from_db(sqlite3 *db, char *data, char *table) {
	char *zErrMsg = 0;
	int rc;
	char *sql;
	const char *text = "Callback function called";

	asprintf(&sql, "SELECT %s FROM %s;", data, table);

	rc = sqlite3_exec(db, sql, callback_print_select, (void *)text, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "Operation done successfully\n");
	}
}


int update_set_string_where_string_db(sqlite3 *db, char *table, char *column, char *data, char *where, char *whereData) {
	char *zErrMsg = 0;
	int rc;
	char *sql;

	asprintf(&sql, "UPDATE %s SET %s = \"%s\" WHERE %s = \"%s\";", table, column, data, where, whereData);

	rc = sqlite3_exec (db, sql, 0, 0, &zErrMsg);
	if(rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return ST_UNCHANGE_LOGIN;
	} else {
		fprintf(stdout, "Operation done successfully\n");
		return ST_CHANGE_LOGIN;
	}
}

int update_set_string_where_string_db_pass(sqlite3 *db, char *table, char *column, char *data, char *where, char *whereData) {
	char *zErrMsg = 0;
	int rc;
	char *sql;

	asprintf(&sql, "UPDATE %s SET %s = \"%s\" WHERE %s = \"%s\";", table, column, data, where, whereData);

	rc = sqlite3_exec (db, sql, 0, 0, &zErrMsg);
	if(rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return ST_UNCHANGE_PASS;
	} else {
		fprintf(stdout, "Operation done successfully\n");
		return ST_CHANGE_PASS;
	}
}

void update_set_int_where_string_db(sqlite3 *db, char *table, char *column, char *data, char *where, char *whereData) {
	char *zErrMsg = 0;
	int rc;
	char *sql;

	asprintf(&sql, "UPDATE %s SET %s = %s WHERE %s = \"%s\";", table, column, data, where, whereData);

	rc = sqlite3_exec (db, sql, 0, 0, &zErrMsg);
	if(rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "Operation done successfully\n");
	}
}

void update_set_string_where_int_db(sqlite3 *db, char *table, char *column, char *data, char *where, char *whereData) {
	char *zErrMsg = 0;
	int rc;
	char *sql;

	asprintf(&sql, "UPDATE %s SET %s = \"%s\" WHERE %s = %s;", table, column, data, where, whereData);

	rc = sqlite3_exec (db, sql, 0, 0, &zErrMsg);
	if(rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "Operation done successfully\n");
	}
}

void update_set_int_where_int_db(sqlite3 *db, char *table, char *column, char *data, char *where, char *whereData) {
	char *zErrMsg = 0;
	int rc;
	char *sql;

	asprintf(&sql, "UPDATE %s SET %s = %s WHERE %s = %s;", table, column, data, where, whereData);

	rc = sqlite3_exec (db, sql, 0, 0, &zErrMsg);
	if(rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "Operation done successfully\n");
	}
}

void delete_from_table_where_int_db(sqlite3 *db, char *table, char *where, char *whereData) {
	char *zErrMsg = 0;
	int rc;
	char *sql;

	asprintf(&sql, "DELETE FROM %s WHERE %s = %s;", table, where, whereData);

	rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
	if(rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "Operation done successfully\n");
	}
}

void delete_from_table_where_string_db(sqlite3 *db, char *table, char *where, char *whereData) {
	char *zErrMsg = 0;
	int rc;
	char *sql;
	
	asprintf(&sql, "DELETE FROM %s WHERE %s = \"%s\";", table, where, whereData);

	rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
	if(rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "Operation done successfully\n");
	}
}

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

t_db_user *mx_create_user(char *login, char *pass) {
    t_db_user *user = malloc(sizeof(t_db_user));

    user->login = strdup(login);
    user->pass = strdup(pass);
    user->token = "1";
    return user;
}

t_db_message *mx_create_message(char *user_login, char *message) {
    t_db_message *t_message = malloc(sizeof(t_db_message));

    t_message->user_login = strdup(user_login);
    t_message->message = strdup(message);
    return t_message;
}

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

void print_table_json(cJSON *root) {
	char *out = cJSON_Print(root);
	printf("%s\n", out);
	free(out);
}

void cJSON_Dresnia() {
	cJSON *root;
	cJSON *cars;
	cJSON *car;

	/* create root node and array */
	root = cJSON_CreateObject();
	cars = cJSON_CreateArray();

	/* add cars array to root */
	cJSON_AddItemToObject(root, "cars", cars);

	/* add 1st car to cars array */
	cJSON_AddItemToArray(cars, car = cJSON_CreateObject());
	cJSON_AddItemToObject(car, "CarType", cJSON_CreateString("BMW"));
	cJSON_AddItemToObject(car, "carID", cJSON_CreateString("bmw123"));

	/* add 2nd car to cars array */
	/*cJSON_AddItemToArray(cars, car = cJSON_CreateObject());
	cJSON_AddItemToObject(car, "CarType", cJSON_CreateString("mercedes"));
	cJSON_AddItemToObject(car, "carID", cJSON_CreateString("mercedes123"));*/

	/* print everything */
	print_table_json(root);

	/* free all objects under root and root itself */
	cJSON_Delete(root);
}

static int callback_sql_to_json(void *data, int argc, char **argv, char **azColName) {
	fprintf(stderr, "%s: ", (const char *)data);

	cJSON *root = cJSON_CreateObject();
	cJSON *somes = cJSON_CreateArray();
	cJSON *some;

	cJSON_AddItemToObject(root, "user", somes);
	cJSON_AddItemToArray(somes, some = cJSON_CreateObject());

	for(int q = 0; q < argc; q++) {
		cJSON_AddItemToObject(some, azColName[q], cJSON_CreateString(argv[q]));
	}

	char *out = cJSON_Print(root);
	printf("%s\n", out);
	free(out);

	cJSON_Delete(root);

	return 0;
}

void sql_to_json(sqlite3 *db, char *data, char *table) {
	char *zErrMsg = 0;
	int rc;
	char *sql;

	asprintf(&sql, "SELECT %s FROM %s;", data, table);

	rc = sqlite3_exec(db, sql, callback_sql_to_json, (void *)table, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "Operation done successfully\n");
	}
}

void json_to_sql_insert_user(sqlite3 *db, cJSON *root) {
	t_db_user *user = NULL;
	cJSON *somes = NULL;
    cJSON *some = NULL;

    somes = cJSON_GetObjectItemCaseSensitive(root, "users");
    cJSON_ArrayForEach(some, somes)
    {
        cJSON *login = cJSON_GetObjectItemCaseSensitive(some, "login");
        cJSON *pass = cJSON_GetObjectItemCaseSensitive(some, "pass");

        user = mx_create_user(login->valuestring, pass->valuestring);
		insert_into_users(db, user);
		free(user);
    }
}

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

cJSON *cJSON_Dresnia_dlia_registration() {
	cJSON *root;
	cJSON *user;

	root = cJSON_CreateObject();
	user = cJSON_CreateObject();

	cJSON_AddItemToObject(root, "user", user);

	cJSON_AddItemToObject(user, "login", cJSON_CreateString("NoviyUser"));
	cJSON_AddItemToObject(user, "pass", cJSON_CreateString("NoviyUserPass"));

	//print_table_json(root);

	return root;
}

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

t_db_user *json_to_user(cJSON *root) {
	t_db_user *user;

	cJSON *json_user = cJSON_GetObjectItemCaseSensitive(root, "user");
	cJSON *login = cJSON_GetObjectItemCaseSensitive(json_user, "login");
    cJSON *pass = cJSON_GetObjectItemCaseSensitive(json_user, "pass");
    user = mx_create_user(login->valuestring, pass->valuestring);

	return user;
}

t_db_message *json_to_message(cJSON *root) {
	t_db_message *t_message;

	cJSON *json_message = cJSON_GetObjectItemCaseSensitive(root, "message");
	cJSON *user_login = cJSON_GetObjectItemCaseSensitive(json_message, "user_login");
    cJSON *message = cJSON_GetObjectItemCaseSensitive(json_message, "message");
    t_message = mx_create_message(user_login->valuestring, message->valuestring);	

	return t_message;
}

cJSON *message_to_json(t_db_message *t_message) {
	cJSON *root;
	cJSON *message;

	root = cJSON_CreateObject();
	message = cJSON_CreateObject();

	cJSON_AddItemToObject(root, "message", message);

	cJSON_AddItemToObject(message, "user_login", cJSON_CreateString(t_message->user_login));
	cJSON_AddItemToObject(message, "date", cJSON_CreateString(t_message->date));
	cJSON_AddItemToObject(message, "message", cJSON_CreateString(t_message->message));

	return root;
}

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

int registration_user(sqlite3 *db, cJSON *root) { 
	t_db_user *user = json_to_user(root);
	int status = 0;

	status = insert_into_users(db, user);

	free(user);
	return status;
}

static int callback_login(void *data, int argc, char **argv, char **azColName) {
	int *status = (int *)data;
	*status = ST_LOG_USER;
	argc = 0;
	argv = NULL;
	azColName = NULL;

	return 0;
}

int login_user(sqlite3 *db, cJSON *root) { 
	t_db_user *user = json_to_user(root);
	char *zErrMsg = 0;
	int rc;
	char *sql;
	int status = ST_UNLOG_USER;

	asprintf(&sql, "SELECT %s FROM %s WHERE login = \"%s\";", "login", "users", user->login);
	rc = sqlite3_exec(db, sql, callback_login, (void *)&status, &zErrMsg);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return ST_UNLOG_USER;
	}

	free(user);
	return status;
}

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

int save_message(sqlite3 *db, cJSON *root) {
	t_db_message *t_message;
	int status = 0;
	
	t_message = json_to_message(root);
	status = insert_into_messages(db, t_message);
	free(t_message);
	return status;
}

static int callback_message_to_client(void *data, int argc, char **argv, char **azColName) {
	t_db_message *t_message;
	cJSON *json_message;
	data = NULL;
	argc = 0;
	azColName = NULL;

	t_message = mx_create_message(argv[1], argv[2]);
	json_message = message_to_json(t_message);

	printf("Отправить клиенту message\n");

	free(t_message);
	cJSON_Delete(json_message);

	return 0;
}

void send_messages_to_client(sqlite3 *db) {
	char *zErrMsg = 0;
	int rc;
	char *sql;

	asprintf(&sql, "SELECT %s FROM %s WHERE date <= datetime('now', 'localtime') AND date >= datetime('now', '-7 day', 'localtime');", "*", "messages");

	rc = sqlite3_exec(db, sql, callback_message_to_client, NULL, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "Operation done successfully\n");
	}
}

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

// int main(int argc, char **argv){
// 	sqlite3 *db = 0;
// 	t_db_user *user = NULL;
// 	t_db_message *message = NULL;
// 	cJSON *root = cJSON_Dresnia_dlia_registration();

// 	db = connect_db(db);
// 	create_table_db(db);

// 	if(argc != 0) {
// 		if(strcmp(argv[1], "11") == 0) {
// 			user = mx_create_user(argv[2], argv[3]);
// 			insert_into_users(db, user);
// 			free(user);
// 		} else if(strcmp(argv[1], "12") == 0) {
// 			message = mx_create_message(argv[2], NULL, argv[3]);
// 			insert_into_messages(db, message);
// 			free(message);
// 		} else if(strcmp(argv[1], "21") == 0) {
// 			update_set_string_where_string_db(db, argv[2], argv[3], argv[4], argv[5], argv[6]);
// 		} else if(strcmp(argv[1], "22") == 0) {
// 			update_set_string_where_int_db(db, argv[2], argv[3], argv[4], argv[5], argv[6]);
// 		} else if(strcmp(argv[1], "23") == 0) {
// 			update_set_int_where_string_db(db, argv[2], argv[3], argv[4], argv[5], argv[6]);
// 		} else if(strcmp(argv[1], "24") == 0) {
// 			update_set_int_where_int_db(db, argv[2], argv[3], argv[4], argv[5], argv[6]);
// 		} else if(strcmp(argv[1], "31") == 0) {
// 			delete_from_table_where_string_db(db, argv[2], argv[3], argv[4]);
// 		} else if(strcmp(argv[1], "32") == 0) {
// 			delete_from_table_where_int_db(db, argv[2], argv[3], argv[4]);
// 		} else if(strcmp(argv[1], "4") == 0) {
// 			select_from_db(db, "*", argv[2]);
// 		} else if(strcmp(argv[1], "41") == 0) {
// 			select_from_db(db, argv[2], argv[3]);
// 		}
// 		else if(strcmp(argv[1], "9") == 0) {
// 			cJSON_Dresnia();
// 		} else if(strcmp(argv[1], "8") == 0) {
// 			sql_to_json(db, "*", argv[2]);
// 		} else if(strcmp(argv[1], "81") == 0) {
// 			sql_to_json(db, argv[2], argv[3]);
// 		} else if(strcmp(argv[1], "82") == 0) {
// 			json_to_sql_insert_user(db, root);
// 		} else if(strcmp(argv[1], "71") == 0) {
// 			registration_user(db, root);
// 		} else if(strcmp(argv[1], "72") == 0) {
// 			login_user(db, root);
// 		} else if(strcmp(argv[1], "61") == 0) {
// 			save_message(db, root);
// 		} else if(strcmp(argv[1], "62") == 0) {
// 			send_messages_to_client(db);
// 		}
// 	}

// 	cJSON_Delete(root);
// 	sqlite3_close(db);

// 	return 0;
// }

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
