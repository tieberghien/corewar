/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_n.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gficara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 21:57:25 by gficara           #+#    #+#             */
/*   Updated: 2018/05/11 09:14:54 by etieberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	count_opts(int ac, char **av)
{
	int i;

	i = 0;
	while (ac-- > 0)
	{
		if (av[ac][0] == '-' || ft_isdigit(av[ac][0]))
			i++;
	}
	return (i);
}

int	id_check(t_champs *champs, t_opts *opts)
{
	int	i;

	i = 0;
	while ((unsigned int)i < opts->n_players)
	{
		if (champs[i].player_id == champs[opts->n_players].player_id)
			return (1);
		i++;
	}
	return (0);
}
