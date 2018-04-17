#include "vm.h"

int fun_exit(char *str, t_champs *champs, t_opts *opts)
{
	int i;

	i = -1;
	while ((unsigned int)++i < opts->n_players)
	{
		ft_strdel(&champs[i].name);
		ft_strdel(&champs[i].comment);
		ft_memdel((void**)&champs[i].instructions);
	}
	if (str)
		return (ft_printf("%s\n", str));
	return (1);
}

int	display_intro(t_champs *champs, t_opts opts)
{
	int i;
	int j;

	i = -1;
	j = 0;
	ft_putendl("Introducing contestants...");
	while ((unsigned)++i < opts.n_players)
	{
		ft_putstr("* Player ");
		ft_putnbr(champs[i].player_id);
		ft_putstr(", weighing ");
		ft_putnbr(champs[i].size);
		ft_putstr(" bytes, \"");
		ft_putstr(champs[i].name);
		ft_putstr("\" (\"");
		ft_putstr(champs[i].comment);
		ft_putendl("\") !");
	}
	fun_exit("All free", champs, &opts);
	return(0);
}
