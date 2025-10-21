#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/wait.h>
#include <fcntl.h> // O_RDONLY, O_WRONLY, O_RDWR


int main(int argc, char* argv[]) {
    printf("Client running...\n");

    char* pipe_sc = "pipe/SERVER_TO_CLIENT";
    char* pipe_cs = "pipe/CLIENT_TO_SERVER";
    char buffer[256];

    // O_RDWR orevents blocking
    int fd_write = open(pipe_cs, O_WRONLY);
    int fd_read  = open(pipe_sc, O_RDONLY);

    if (fd_read == -1 || fd_write == -1) {
        perror("Error opening pipes");
        return -1;
    }

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        ssize_t n = read(fd_read, buffer, sizeof(buffer) - 1);

        if (n > 0) { 
            buffer[n] = '\0';
            printf("\n[Server]: %s\n", buffer);

            // get user input
            printf("[Client]: ");
            fflush(stdout);

            memset(buffer, '\0', sizeof(buffer));
            if (fgets(buffer, sizeof(buffer), stdin) == NULL)
                break;

            // remove newline if present
            char* newline = strchr(buffer, '\n');
            if (newline) *newline = '\0';

            // send to server
            write(fd_write, buffer, strlen(buffer));
        } 
        else if (n == 0) {
            printf("Server closed the connection.\n");
            break;
        } 
        else {
            perror("read");
            break;
        }
    }

    close(fd_read);
    close(fd_write);
    return 0;
}










