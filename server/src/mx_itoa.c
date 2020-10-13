#include "server.h"

static int digitlen(long n) {
    unsigned int len = 0;

    if (n < 0) {
        n *= -1;
	    len++;
    }
    while (n > 0) {
        n /= 10;
        len++;
    }
    return len;
}

char *mx_itoa(int number) {
    char *res;
    long n = number;
    int count = digitlen(n);
    int min = 0;
    
    res = mx_strnew(count);
    if (n == 0) {
        res[0] = '0';
        return res;
    }
    if (n < 0) {
        res[0] = '-';
        min++;
        n *= -1;
    }
    for (int i = count - 1; i >= min; i--) {
        res[i] = (n % 10) + '0';
        n /= 10;
    }
    return res;
}
