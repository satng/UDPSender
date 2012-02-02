#ifndef UDP_SENDER_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>

#define DEF_PORT 30303
#define DEF_HOST "192.168.1.255"
//#define DEF_HOST "192.168.0.255"
#define DEF_MESSAGE "{\"exec\":{\"dev\":\"e4:ce:8f:15:6d:8a\",\"time\": 12345, \"pwd\":\"xxx\",\"grp\":0,\"op\":1,\"ack\":true,\"argc\":1,\"argv\":[{\"type\":\"int\",\"value\":3}]}}"

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
