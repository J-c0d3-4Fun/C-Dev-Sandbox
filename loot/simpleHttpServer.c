
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#define BACKLOG 10
#define BUFFER_SIZE 1024

volatile sig_atomic_t running = 1;
int server_fd = -1;
int client_fd = -1;

void handle_sigint(int sig) {
    (void)sig;
    running = 0;
    if (client_fd != -1) close(client_fd);
    if (server_fd != -1) close(server_fd);
}

int main(int argc, char *argv[]){
    signal(SIGINT, handle_sigint);
    
    
    struct sockaddr_storage their_addr;
    socklen_t addr_size;
    struct addrinfo hints, *res;
    int status;
    int bytes;
    int sockfd, new_fd;
    char buffer[BUFFER_SIZE] = {0};

    if(argc != 2) {
        fprintf(stderr, "usage: <script name> <port number>");
        return 1;
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if (((status = getaddrinfo(NULL, argv[1], &hints, &res))) != 0){
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 2;
    }

    if ((sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1){
        fprintf(stderr, "socket: %s\n", strerror(errno));
        return 2;
    }
    server_fd = sockfd;  // store globally for signal handler
    printf("Socket created (fd=%d)\n", sockfd);
    
    int yes = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes);
    if ((status = bind(sockfd, res->ai_addr, res->ai_addrlen)) == -1){
        fprintf(stderr, "bind: %s\n", strerror(errno));
        return 2;
    }
    freeaddrinfo(res);
    printf("Bound to port %s\n", argv[1]);

    
    if (listen(sockfd, BACKLOG) == -1){
        fprintf(stderr, "listen: %s\n", strerror(errno));
        return 2;
    }
    printf("Listening on port %s...\n", argv[1]);

    while (running) {
        
        addr_size = sizeof(their_addr);
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
        if (new_fd == -1) {
            if (!running) break;  // signal caught, exit loop
            continue;
        }
        printf("Accepted connection (fd=%d)\n", new_fd);
        client_fd = new_fd;  // store for signal handler
        
        while (running && (bytes = recv(new_fd, buffer, BUFFER_SIZE - 1, 0)) > 0) {
            if(bytes == -1){
                perror("recv");
                break;
            }
            buffer[bytes] = '\0';
            printf("Command: %s\n", buffer);
            send(new_fd, "ACK\n", 4, 0);
        }

        close(new_fd);
        client_fd = -1;
        printf("Client disconnected\n");
    }

    printf("\nServer shut down\n");
    return 0;
}