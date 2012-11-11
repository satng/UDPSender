#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <udp_sender.h>

#define CONST_HOST 1
#define CONST_PORT 2
#define CONST_MSG 3

int main(int argc, char *argv[]) { 
    container *c = (void *) malloc(sizeof(container));
    
    if (argc != 4) {
        fprintf(stderr, "Error in usage: %s <host> <port> <message>\n", argv[0]);
        printf("Using default value: %s:%d %s\n", DEF_HOST, DEF_SEND_PORT, DEF_MESSAGE);
        c->port = DEF_SEND_PORT;
        c->host = DEF_HOST;
        c->message = DEF_MESSAGE;
    } else {
        c->host = argv[CONST_HOST];
        c->port = atoi(argv[CONST_PORT]);
        c->message = argv[CONST_MSG];
    }
    
    if ((c->fd  = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        perror("socket");
    
    if (setsockopt(c->fd, SOL_SOCKET, SO_BROADCAST, (void *) &_bp, sizeof(_bp)) < 0)
        perror("setsockopt()");
    
    memset(&c->addr, 0, sizeof(c->addr));
    c->addr.sin_family = AF_INET;
    c->addr.sin_addr.s_addr = inet_addr(c->host);
    c->addr.sin_port = htons(c->port);
    
    unsigned int msg_len = strlen(c->message);
    
    while(1) {
        if (sendto(c->fd, c->message, msg_len, 0, (struct sockaddr *) &c->addr, sizeof(c->addr)) != msg_len)
            perror("sendto() sent a different number of bytes than expected");
        else 
            printf("[+] Sending to %s:%d\n", \
                    //"[+] ^C to end.\n" 
                    c->host, c->port);
        sleep(3);
    };
    
    return EXIT_SUCCESS;
}

