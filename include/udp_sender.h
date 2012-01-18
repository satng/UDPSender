#ifndef UDP_SENDER_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>

typedef enum {true, false} boolean;
const unsigned int _bp = 1;

typedef struct container {
    struct sockaddr_in addr;
    int fd;
    char *message;
    char *host;
    int port;
} container;

//unused right now!
void set_broadcast();
void send_message();
void *_run_sender_thread(void *arg);
#endif
