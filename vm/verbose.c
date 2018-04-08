void	verbose_one(t_champ *champ);

void	verbose_zero(t_champ champ);
{
	ft_putstr("le joueur");
	ft_putnbr(champ.player_id);
	ft_putchar('(');
	ft_putstr(champ.name);
	ft_putchar(')');
	ft_putstr(" a gagne");	
}
