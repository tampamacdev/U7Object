#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define PORT 8080           // Default port to listen on
#define BUFFER_SIZE 1024    // Buffer size for receiving data
#define BACKLOG 5           // Number of pending connections in queue

void error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main() {
    int server_fd, client_fd;              // File descriptors for server and client sockets
    struct sockaddr_in server_addr, client_addr; // Server and client address structures
    socklen_t client_len = sizeof(client_addr);  // Length of client address
    char buffer[BUFFER_SIZE];              // Buffer for incoming data

    // Create socket (AF_INET for IPv4, SOCK_STREAM for TCP)
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        error("Socket creation failed");
    }

    // Set socket options to reuse address (avoids "Address already in use" errors)
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        error("Setsockopt failed");
    }

    // Initialize server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;           // IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY;   // Bind to any interface (0.0.0.0)
    server_addr.sin_port = htons(PORT);         // Convert port to network byte order

    // Bind socket to address and port
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        error("Bind failed");
    }

    // Listen for incoming connections
    if (listen(server_fd, BACKLOG) < 0) {
        error("Listen failed");
    }

    printf("Listening on port %d...\n", PORT);

    // Accept a client connection
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
    if (client_fd < 0) {
        error("Accept failed");
    }

    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
    printf("Client connected from %s:%d\n", client_ip, ntohs(client_addr.sin_port));

    // Receive and echo data
    ssize_t bytes_received;
    while ((bytes_received = recv(client_fd, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        buffer[bytes_received] = '\0'; // Null-terminate the received data
        printf("Received: %s", buffer);

        // Echo back to client (optional, remove if pure listener)
        if (send(client_fd, buffer, bytes_received, 0) < 0) {
            error("Send failed");
        }
    }

    if (bytes_received < 0) {
        error("Recv failed");
    }

    printf("Client disconnected\n");

    // Cleanup
    close(client_fd);
    close(server_fd);

    return 0;
}
