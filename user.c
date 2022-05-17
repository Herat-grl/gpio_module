#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

#define BUFFER_LENGTH 40

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_LENGTH 40

char *read_line (char *buf, size_t length, FILE *f)
{
    char *p;
    if (p = fgets (buf, length, f)) {
        size_t last = strlen(buf) - 1;
        if (buf[last] == '\n') {
            buf[last] = '\0';
        } else {
            fscanf (f, "%*[^\n]");
            (void) fgetc (f);
        }
    }
    return p;
}

int main () {
    int num, data;
    char line[BUFFER_LENGTH];
    char *buf = malloc(sizeof(int)*5);

    ssize_t f = open ("/dev/phy_intr", O_RDWR);
    if (f == -1) {
        printf ("Couldn't open the device.\n");
        return 0;
    } else {
        printf ("Opened the device: file handle #%lu!\n", (long unsigned int)f);
    }
    

    do {
        printf("       1 : test gpio9 & gpio15 with 0 value\n");
        printf("       2 : test gpio9 & gpio15 with 1 value\n");
        printf("       3 : test gpio25 & gpio16 with 0 value\n");
        printf("       4 : test gpio25 & gpio16 with 1 value\n");    
        printf("       10: exit\n");
        read_line(line, BUFFER_LENGTH, stdin);
        num = strtol(line, NULL, 10);

        if(num == 1) {
            buf[0] = 0;
            buf[1] = 1;
            read (f, buf, 2);
            printf("value : %d\n", buf[0]);
        } else if(num == 2) {
            buf[0] = 1;
            buf[1] = 1;
            read (f, buf, 2);
            printf("value : %d\n", buf[0]);
        } else if(num == 3) {
            buf[0] = 0;
            buf[1] = 2;
            read (f, buf, 2);
            printf("value : %d\n", buf[0]);
        } else if(num == 4) {
            buf[0] = 1;
            buf[1] = 2;
            read (f, buf, 2);
            printf("value : %d\n", buf[0]);
        } else if(num == 10) {
            printf("exit...");
        } else {
            printf("invalid input\n");
        }
    }while(num != 10);
    close (f);
    return 0;
}
