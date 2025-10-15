#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <err.h>
#include <fcntl.h> // O_RDONLY, O_WRONLY
/**
 * 	gcc -c -lcrypt server.c
 * 	gcc -lcrypt server.c -o server
 */

/**
 *	Server should access a file that contains 
 *	valid usernames and passwords in /users/information.txt
 *	take username and decrypt hashed password with input password.
 *	IF accepted, 
*/


static int num_commands(char* command_line);
static int digits(int num);


static int digits(int num) {
    int n = 0;
    while (num != 0) {
        num /= 10;
        n++;
    }
    return n;
}

static int num_commands(char* command_line) {
    int num = 0;
    for (int i = 0; i < strlen(command_line); i++) {
        if (command_line[i] == ' ' ||
            command_line[i] == '\n') num++;
    }
    return num;
}


int main() {
	
    printf("Server running...\n");

    // assume access granted
    char* valid_message = "+ACCOUNT VALID";
    char* nonvalid_message = "-INVALID ACCOUNT\n+GOODBYE";

    // add validation
    

    // continue logic 
	char* pipe_sc    = "pipe/SERVER_TO_CLIENT";
	char* pipe_cs    = "pipe/CLIENT_TO_SERVER";
    char buffer[256] = "Connected to server -> PID: ";
 
    mkdir("pipe", 0700);
    mkfifo(pipe_sc, 0600);
    mkfifo(pipe_cs, 0600);
    
	int fd_read  = open(pipe_cs, O_RDONLY);
	int fd_write = open(pipe_sc, O_WRONLY);

    // write first (Connected to server, PID: getpid())
    sprintf(buffer, "%d", getpid());
    buffer[strlen(buffer)] = '\0';
    write(fd_write, buffer, strlen(buffer));
    
    printf("%s\n", buffer);
    while(1) {
        // read first
        // after reading finished (n > ), proceed
        // with writing
        ssize_t n = read(fd_read, buffer, sizeof(buffer));
        buffer[n] = '\0';
        if (n > 0) {
            printf("%s\n", buffer);

            // argv[0]: prog_name
            // argv[1]: range
            // argv[2]: upper_bound
            
            // fork here and do exec for worker located
            // in "../boss_worker_c/worker"
            
            int status;
            pid_t pid = fork();
            
            if (pid == 0) {
                char argv[4][128];
                printf("Enter child process.\n");

                // keep as 31 to allow for null terminator
                sscanf(buffer, "%127s %127s %127s %127s",
                        argv[0], argv[1], argv[2], argv[3]);
                
                printf("Execute: %s %s %s %s\n", argv[0], argv[1], argv[2], argv[3]);
                execl(argv[0], argv[1], argv[2], argv[3], (char *)NULL);
            } 
            else {
                // wait for child process to complete
                wait(&status);
                
                // return pid to client
                sprintf(buffer, "%d", status);
                sprintf(buffer, "%d", status);
                buffer[digits(status)] = '\0';
                write(fd_write, buffer, strlen(buffer));

            }
        }
    }

    close(fd_read);
    close(fd_write);
    unlink(pipe_sc);
    unlink(pipe_cs);

    return 0;
}





