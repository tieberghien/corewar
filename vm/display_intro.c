void	display_intro(t_champ *champs, t_opts opts)
{
	int i;
	int id;

	i = -1;
	j = 0;
	ft_putendl("Introducing contestants...");
	while (++i < opts.n_players)
	{
		ft_putstr("* Player ");
		ft_putnbr(champs[i].player_id);
		ft_putstr(", weighing ");
		ft_putnbr(champs[i].weight);
		ft_putstr(" bytes, \"");
		ft_putstr(champs[i].name);
		ft_putstr("\" \(\"");
		ft_putstr(champs[i].comment);
		ft_putendl("\"\) !");
		i++;
	}
}
