/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_n.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gficara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 21:57:25 by gficara           #+#    #+#             */
/*   Updated: 2018/05/10 22:21:25 by gficara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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
