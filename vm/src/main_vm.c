/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etieberg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:21:37 by etieberg          #+#    #+#             */
/*   Updated: 2018/03/16 17:24:56 by etieberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	display_usage(void)
{
	return ;
}

static void	parse_opts(char **ops)
{
	return ;
}

int		main(int ac, char **av)
{
	int		i;
	t_opts	opts;
	t_champs	*c;

	i = 1;
	if (ac < 2)
		display_usage();
	bzero(&opts, sizeof(t_opts));
	while (i < ac && av[i][0] == '-' && av[i][1] != '\0')
	{
		if (av[i][1] == '-')
		{
			i++;
			break ;
		}
		parse_options(av[i], &opts);
		i++;
	}
	c = NULL;
	register_champs(c);
	begin_game(c);
	while (1)
	{
		if (!corewar_game())
			display_result();
	}
	return (0);
}
