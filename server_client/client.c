#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/wait.h>
#include <fcntl.h> // O_RDONLY, O_WRONLY

int arg_valid(int argc, char* argv[]);


int arg_valid(int argc, char* argv[]) {
	if (argc != 3) return -1;
	return 0;
}

/**
 *	@brief Client gets username and password from user:
 *		USER <username> <password>
 *
 *		IF account is validated, prompts user for parameters 
 *		of program that server will execute on behalf of the client:
 *		SUCCESS: +ACCOUNT VALID
 *		FAIL   : -INVALID ACCOUNT
 *
 *		EXEC <path of command> <command> <par1> ... <parN>
 *		
 *		IF exec is successful, server will return PID of process
 *		via the message:
 *			+EXEC SUCCESSFUL PID <XXXX> ((XXXX) == PID of process)
 *		ELSE IF exec fails, the server responds with:
 *			-EXEC FAILED  -> exchange is ended
 */
int main(int argc, char* argv[]) {
    
	//if (arg_valid(argc, argv) != 0) return -1;	
	
    printf("Client running...\n");

    char* pipe_sc    = "pipe/SERVER_TO_CLIENT";
	char* pipe_cs    = "pipe/CLIENT_TO_SERVER";
    char buffer[256];
	/*
	 * pipe() is anonymous pipe (unidirectional)
	 * mkfifo() is name pipe (either bi-directional or uni-directional)
	 * 		USE mkfifo()
	 */

	int fd_write = open(pipe_cs, O_WRONLY);
	int fd_read  = open(pipe_sc, O_RDONLY);
    if (fd_read == - 1 || fd_write == -1) return -1;
	
	while (1) {
        ssize_t n = read(fd_read, buffer, sizeof(buffer));
        // n == length of message
        // message received from server
        if (n > 0) {
            printf("\nMessage received: %s\n", buffer);

            // user enter response to server
            printf("Send Message: ");
            fgets(buffer, sizeof(buffer), stdin);
            char* null_term_loc = strstr(buffer, "\n");
            null_term_loc = '\0';

            write(fd_write, buffer, strlen(buffer) + 1);
        }
    }

    close(fd_read);
    close(fd_write);

    unlink(pipe_sc);
    unlink(pipe_cs);
	
    return 0;
}














