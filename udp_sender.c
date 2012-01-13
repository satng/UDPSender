#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <udp_sender.h>
#include <unistd.h>

#define CONST_HOST 1
#define CONST_PORT 2
#define CONST_MSG 3

int main(int argc, char *argv[]) { 
    struct sockaddr_in addr;
    int fd;
    int _bp = 1;
    unsigned int msg_len = 0;
    
    if (argc != 4) {
        fprintf(stderr, "Error in usage: %s <host> <port> <msg>\n", argv[0]);
        return -1;
    }

    char *message = argv[CONST_MSG];
    char *host = argv[CONST_HOST];
    unsigned short port = atoi(argv[CONST_PORT]);
    
    printf("[+] Sending to %s:%d\n", host, port);

    if ((fd  = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        perror("socket");
    
    if (setsockopt(fd, SOL_SOCKET, SO_BROADCAST, (void *) &_bp, sizeof(_bp)) < 0)
        perror("setsockopt()");

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(host);
    addr.sin_port = htons(port);
    
    msg_len = strlen(message);
    while (1) {
        if (sendto(fd, message, msg_len, 0, (struct sockaddr *) &addr, sizeof(addr)) != msg_len)
            perror("sendto() sent a different number of bytes than expected");
        sleep(3);
    }
}

