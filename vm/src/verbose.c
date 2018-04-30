void	verbose_one(t_champs champ);
{
	ft_putstr("un processus dit que le joueur "); 
	ft_putstr(champ.name);
	ft_putstr(" est en vie\n");
}
void	verbose_zero(t_champs champ);
{
	ft_putstr("le joueur");
	ft_putnbr(champ.player_id);
	ft_putchar('(');
	ft_putstr(champ.name);
	ft_putchar(')');
	ft_putstr(" a gagne");	
}
