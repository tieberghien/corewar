#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int     main(void)
{
    int fd;
    int i;
    char a;

    i = -1;
    a = 'a';
    fd = open("verif.s", O_CREAT | O_WRONLY, 0644);
    if (fd == -1)
        printf("file not open");
    else
    {
        write(fd, ".name\"", 6);
        while (++i < 129)
            write(fd, &a, 1);
        write(fd, "\"\n", 2);
        write(fd, ".comment\"", 9);
        i = -1;
        while (++i < 2048)
            write(fd, &a, 1);
        write(fd, "\"\n", 2);
    }
    return (0);
}