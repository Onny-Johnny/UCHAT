#include "server.h"

void make_demon() {
    if (fork() != 0 ) {
        exit(0);
    }
    umask(0);
    setsid();
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}
