#include <stdio.h>

int main() {
    char buffer[1024]; // Buffer for input

    printf("Waiting for keyboard input (Ctrl+D or Ctrl+Z to exit):\n");

    // Infinite for loop to wait for input
    for (;;) { // Same as while (1)
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            printf("Received input: %s", buffer);
            fflush(stdout); // Ensure output is immediate
        } else {
            // EOF (Ctrl+D on Unix, Ctrl+Z on Windows) or error
            if (feof(stdin)) {
                printf("EOF detected\n");
                break;
            } else {
                perror("Error reading input");
                break;
            }
        }
    }

    return 0;
}
