#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <udp_sender.h>

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    int sockfd;
    char buffer[1024];
    struct sockaddr_in serv_addr;
    int m_port = -2;
    char *m_host = (char *) malloc(sizeof(char));
    
//    if (argc < 2) {
//        printf("ATTENTION: no host provided. Insert your local address.\n");
//        return 1;
//    } else {
        int counter;
        while ( (counter = getopt(argc, argv, "h:p:v:")) != -1 )
            switch (counter) {
            case 'p':
                m_port = atoi(optarg);
                break;
            case 'h':
                m_host = optarg;
                break;
            case 'v':
                printf("The usage. To be implemented.\n");
                return 0;
                break;
            default:
                m_port = DEF_PORT;
            }
    //}   
    
    //m_port = DEF_PORT;
    //m_host = argv[1];
    
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
    
    struct ip_mreq group;
    group.imr_multiaddr.s_addr = inet_addr(DEF_HOST);
    group.imr_interface.s_addr = inet_addr(m_host);
    
    if (setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *)&group, sizeof(group)) < 0) {
        perror("Multicast error");
        close(sockfd);
        exit(1);
    }
    
    printf("Try to read from %s:%d\n", m_host, m_port);
    
    if (read(sockfd, buffer, sizeof(buffer)) < 0) 
       error("ERROR: reading from socket");
    else
        printf("Here is the message: %s\n", buffer);
     
    close(sockfd);
    free(m_host);
    return 0; 
}
