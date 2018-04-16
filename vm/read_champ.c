#include "vm.h"

int read_file(t_champs *champs)
{
    int i;
    int j;
    unsigned char buf[4];

    j = 0;
    while ((i = read(champs->fd, buf, 4)) > 0)
    {
        j += i;
    }
    return (ft_printf("number of data read = %d\n", j));
}

int	oc_file(t_champs *champs, t_opts *opts)
{
    unsigned int i;

    i = 0;
    while (i < opts->n_players)
    {
        
        champs[i].fd = open(champs[i].file_name, O_RDONLY);
        //ft_printf("player %s id %d open: %d\n", champs[i].file_name, champs[i].player_id, champs[i].fd);
        if (champs[i].fd == -1)
            return (ft_printf("File not open"));
        read_file(champs + i);
        close(champs[i].fd);
        i++;
    }
    return (0);
}
