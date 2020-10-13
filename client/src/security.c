#include "client.h"

// char *init_salt(unsigned char *hash) {
// 	char *alphanum = strdup("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
// 	int str_len = sizeof(alphanum) - 1;
// 	char *salt;
// 	short gen_key;

// 	srand(time(NULL));
// 	salt = (char *)malloc(sizeof(char) * SHA512_DIGEST_LENGTH + 1);
// 	for (int i = 0; i < SHA512_DIGEST_LENGTH + 1; i++) {
// 		gen_key = rand() % str_len;
// 		salt[i] = alphanum[key];
// 	}
// 	salt[SHA512_DIGEST_LENGTH + 1] = '\0';
// 	free(alphanum);
// 	alphanum = NULL;
// 	return salt;
// }

// char *hash(char *pass) {
//     unsigned char sha512[SHA512_DIGEST_LENGTH];
//     char *hash;
//     char *str = NULL;

//     asprintf(&hash, "%s", pass);
//     SHA512((unsigned char *)hash, strlen(hash), sha512);
//     free(hash);
//     while (mx_strlen(str)!= 64) {
//         str = init_salt(sha512);
//     }
//     return str;
// }
