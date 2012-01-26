#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <udp_sender.h>

#define CONST_HOST 1
#define CONST_PORT 2
#define CONST_MSG 3

void *_run_sender_thread(void *arg) {
    container *c = (void *) malloc(sizeof(container)); 
    c = ((container*)(arg));
    
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
    
   free(c);
    pthread_exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) { 
    pthread_t th;
    container *ct;
    ct = (void *) malloc(sizeof(container));
    
    if (argc != 4) {
        fprintf(stderr, "Error in usage: %s <host> <port> <message>\n", argv[0]);
        printf("Using default value: %s:%d %s\n", DEF_HOST, DEF_PORT, DEF_MESSAGE);
        ct->port = DEF_PORT;
        ct->host = DEF_HOST;
        ct->message = DEF_MESSAGE;
    } else {
        ct->host = argv[CONST_HOST];
        ct->port = atoi(argv[CONST_PORT]);
        ct->message = argv[CONST_MSG];
    }
    
    if (pthread_create(&th, NULL, _run_sender_thread(ct), NULL) != 0)
        perror("creation of thread fail: ");
    
    pthread_join(th, NULL);
    free(ct);
    return EXIT_SUCCESS;
}

