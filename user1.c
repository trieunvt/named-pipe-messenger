/**
 * @author:  trieunvt
 * @date:    26 Jul 2024
 * @version: v1.0.0
**/

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define ARRAY_SIZE 1024

int main(void) {
    int read_fd, write_fd;
    char read_array[ARRAY_SIZE], write_array[ARRAY_SIZE];

    /* Create named pipe to transfer message from user 1 to user 2 */
    mkfifo("named_pipe_f1t2", 0666);

    /* Create parent and child processes using fork() */
    if (fork()) {
        while (1) {
            /* Parent process */
            /* Open named pipe for writing only */
            write_fd = open("named_pipe_f1t2", O_WRONLY);
            fgets(write_array, ARRAY_SIZE, stdin);
            write(write_fd, write_array, strlen(write_array) + 1);
            close(write_fd);
        }
    } else {
        while (1) {
            /* Child process */
            /* Open named pipe for reading only */
            read_fd = open("named_pipe_f2t1", O_RDONLY);
            read(read_fd, read_array, sizeof(read_array));
            printf("[2]: %s", read_array);
            close(read_fd);
        }
    }

    return 0;
}
