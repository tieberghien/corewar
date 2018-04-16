#include "vm.h"

int readstr(unsigned char **str, int buffsize, unsigned char *buf, int fd)
{
    int i;

    i = read(fd, buf, buffsize);
    if (!(*str = (char*)malloc(sizeof(char) * buffsize + 1)))
        return (-1);
    (*str)[buffsize] = '\0';
    *str = ft_strncpy(*str, buf, buffsize);
    return (i)
}

int read_file(t_champs *champs)
{
    int i;
    int j;
    unsigned char buf[COMMENT_LENGTH];

    j = 0;
    i = read(champs->fd, buf, 4);
    if (ft_memcmp((void *)buf, g_magic, 4))
       return(ft_printf("did you try to trick me? you're not a real.cor...    %d\n", j));
    j += i;
    if((i = readstr(&champs->name, PROG_NAME_LENGTH, buf, champs->fd)) < 0)
        ft_printf("malloc error");
    j += i;
    i = read(champs->fd, buf, 4);
    if (buf[0] != 0  buf[1] != 0 || buf[2] * 256 + buf[3] > CHAMP_MAX_SIZE)
        return (ft_printf("%s is too big", champs->name));
    if((i = readstr(champs->comment, COMMENT_LENGTH, buf, champs->fd)) < 0)
        ft_printf("malloc error");
    j += i;
    if (i)
    return (ft_printf("number of data read = %d\n", j));
}

int	oc_file(t_champs *champs, t_opts *opts)
{
    unsigned int i;

    i = 0;
    while (i < opts->n_players)
    {
        champs[i].fd = open(champs[i].file_name, O_RDONLY);
        if (champs[i].fd == -1)
            return (ft_printf("File not open"));
        if (lseek(champs[i].fd, 4, SEEK_SET) == -1)
            return(ft_printf("champion %s is a lie!", champs[i].file_name));
        if (lseek(champs[i].fd, PROG_NAME_LENGTH, SEEK_CUR) == -1)
            return(ft_printf("champion %s is a lie!", champs[i].file_name));
        if (lseek(champs[i].fd, 4, SEEK_CUR) == -1)
            return(ft_printf("champion %s is a lie!", champs[i].file_name));    
        if (lseek(champs[i].fd, COMMENT_LENGTH, SEEK_CUR) == -1)
            return(ft_printf("champion %s is a lie!", champs[i].file_name));
        lseek(champs[i].fd, 0, SEEK_SET);
        read_file(champs + i);
        close(champs[i].fd);
        i++;
    }
    return (0);
}
