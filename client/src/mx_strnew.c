#include "client.h"

char *mx_strnew(const int size) {
    char *str;
    int i = 0;
    
    if(size < 0)
        return 0;
    str =(char*)malloc(sizeof(char)*(size + 1));
    if(str == NULL)
        return NULL;
    while(i < size + 1){
        str[i] = '\0';
        i++;
    }
    return str;
}
