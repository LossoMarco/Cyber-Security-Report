#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024
#define SERVER_PORT 8080

int main() {
    char buffer[BUFFER_SIZE];
    int server_sockfd, client_sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    FILE *file;

    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sockfd < 0) {
        perror("Error creating socket");
        return 1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(server_sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error binding socket");
        return 1;
    }

    if (listen(server_sockfd, 1) < 0) {
        perror("Error listening on socket");
        return 1;
    }

    printf("Server is listening on port %d\n", SERVER_PORT);

    client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_addr, &client_len);
    if (client_sockfd < 0) {
        perror("Error accepting connection");
        return 1;
    }

    file = fopen("output.txt", "a");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    ssize_t n;
    while ((n = read(client_sockfd, buffer, BUFFER_SIZE)) > 0) {
        fwrite(buffer, sizeof(char), n, file);
    }

    fclose(file);
    close(client_sockfd);
    close(server_sockfd);

    return 0;
}