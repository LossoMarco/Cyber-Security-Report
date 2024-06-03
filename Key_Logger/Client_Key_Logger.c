#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_BUFFER_SIZE 1024

int main() {
    const char *filename = "log.txt";
    const char *server_ip = "10.0.2.15";
    int server_port = 8080;

    // Open the file
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return 1;
    }

    // Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        printf("Could not create socket\n");
        return 1;
    }

    // Specify server details
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(server_port);
    if (inet_pton(AF_INET, server_ip, &(server_address.sin_addr)) <= 0) {
        printf("Invalid server IP\n");
        return 1;
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        printf("Connection failed\n");
        return 1;
    }

    // Read file and send its content
    char buffer[MAX_BUFFER_SIZE];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, MAX_BUFFER_SIZE, file)) > 0) {
        write(sock, buffer, bytes_read);
    }

    // Cleanup
    fclose(file);
    close(sock);

    return 0;
}