#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("file.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    printf("Opened file descriptor: %d\n", fd);
	close(fd);
    // Do something with the file descriptor here...
int fd2 = open("file.txt", O_RDONLY);
    if (fd2 == -1) {
        perror("open");
        exit(1);
    }
    printf("Opened file descriptor: %d\n", fd2);
int fd3 = open("file.txt", O_RDONLY);
    if (fd3 == -1) {
        perror("open");
        exit(1);
    }
    printf("Opened file descriptor: %d\n", fd3);
    return 0;
}
