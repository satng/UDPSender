#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <udp_sender.h>
#include <udp_ports.h>

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    int sockfd;
    char buffer[1024];
    struct sockaddr_in serv_addr;
    int m_port = -1;
    int counter;
    
    if (argc < 2 ) {
        printf("Error in usage: try %s -h\n", argv[0]);
        return 1;
    }
    
    while ( (counter = getopt(argc, argv, "p:h")) != -1 )
        switch (counter) {
        case 'p':
            m_port = atoi(optarg);
            break;
        case 'h':
            printf("Options available:\n\t-p:\tthe port\n");
            return 1;
        default:
            printf("Error in usage, try with: %s -h\n", argv[0]);
            return 1;
        }
    
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("ERROR opening socket");
        exit(1);
    }
    
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (void *) &_bp, sizeof(_bp)) < 0) {
        perror("setsockopt()");
        close(sockfd);
        exit (1);
    }

    memset((void *) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(m_port);
    
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error on binding");
        close(sockfd);
        exit(1);
    }
   
    printf("Try to read from localhost:%d\n", m_port);
    
    while (read(sockfd, buffer, sizeof(buffer)) != -1)
        printf("%s\n\n", buffer);
     
    close(sockfd);
    //free(m_host);
    return 0; 
}
