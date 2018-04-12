#include "vm.h"

int	main(int ac, char **av)
{
	t_opts opts;
	int		i;
	int		j;
	int		k;

	opts.s_cycles = 0;
	opts.n_players = 0;
	i = 0;
	j = 0;
	if (i == ac)
		return (ft_printf("no player"));
	while (++i < ac)
	{
		if (j == 1)
		{
			k = 0;
			while (str[k] >= '0' && str[k] <= '9')
				k++;
			if (str[i])
				return (ft_printf("not a number"))
			ft_atoi(av[i]);
		}
		else if (!ft_strcmp("-dump", av[i]) && j != 1)
			j = 1;
		else if (!ft_strcmp("-n", av[i]) && j != 1)
			j = 1;
		else if (ft_strstr(av[i], ".cor"))
			opts.n_player++;
		else
			return (ft_printf("invalid player"));
	}
}
