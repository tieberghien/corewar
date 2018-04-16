#include "vm.h"

int	parsing_arg_b(char *str, t_opts *opts, int *j)
{
	int	k;

	k = 0;
	while (str[k] >= '0' && str[k] <= '9')
		k++;
	if (str[k])
		return (ft_printf("not a number\n"));
	if (*j == 1)
	{
		if (opts->s_cycles != 0)
			return (ft_printf("more than 1 dump command\n"));
		opts->s_cycles = ft_atoi(str);
		j = 0;
	}
	else
		*j = -1;
	return (0);
}


int	parsing_arg_a(int ac, char **av, t_opts *opts)
{
	int	i;
	int	j;
	char *par;

	i = 0;
	j = 0;
	while (++i < ac)
	{
		if (j > 0)
		{
			if (parsing_arg_b(av[i], opts, &j))
				return (1);
		}
		else if (!ft_strcmp("-dump", av[i]) && j == 0)
			j = 1;
		else if (!ft_strcmp("-n", av[i]) && j == 0)
			j = 2;
		else if (ft_strcmp(av[i], ".cor") &&
				(par = ft_strstr(av[i], ".cor")) && j < 1)
		{
			if (ft_strcmp(".cor",par) || par[-1] == '/')
				return(ft_printf("invalid player"));
			opts->n_players++;
			if (opts->n_players> MAX_PLAYERS)
				return (ft_printf("too many player\n"));
			j = 0;
		}
		else
			return (ft_printf("invalid player\n"));
	}
	if (1 == ac || opts->n_players == 0 || j != 0)
		return (ft_printf((j == 0) ? "no player\n" : "missing player"));
	return (0);
}

int	main(int ac, char **av)
{
	t_opts opts;

	if (MAX_PLAYERS < 1)
		ft_printf("MAX_PLAYERS not properly defined");
	opts.s_cycles = 0;
	opts.n_players = 0;
	if (parsing_arg_a(ac, av, &opts))
		return (1);
	ft_printf("number of player: %d", opts.n_players);
}
