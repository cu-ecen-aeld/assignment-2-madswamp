#include <syslog.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>


int main(int argc, char *argv[]) {
    openlog("writer", LOG_PID, LOG_USER);
    if (argc != 3) {
        syslog(LOG_ERR, "Not enough arguments provided. Usage: %s <filename> <string>", argv[0]);
        printf("Usage: %s <filename> <string>\n", argv[0]); //For debugging purposes
        return 1;
    }
    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd == -1) {
        syslog(LOG_ERR, "Failed to open file: %s", argv[1]);
        printf("Failed to open file: %s\n", argv[1]); //For debugging purposes
        return 1;
    }

    syslog(LOG_DEBUG, "Writing %s to file: %s", argv[2], argv[1]);
    printf("Writing %s to file: %s\n", argv[2], argv[1]); //For debugging purposes

    ssize_t bytes_written = write(fd, argv[2], strlen(argv[2]));
    if (bytes_written == -1) {
        syslog(LOG_ERR, "Failed to write to file: %s", argv[1]);
        printf("Failed to write to file: %s\n", argv[1]); //For debugging purposes
        close(fd);
        return 1;
    }

    close(fd);
    closelog();

    return 0;
}