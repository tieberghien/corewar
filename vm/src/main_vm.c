/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etieberg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:21:37 by etieberg          #+#    #+#             */
/*   Updated: 2018/03/16 15:49:49 by etieberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	display_usage(void)
{
	return ;
}

static void	parse_opts(char **ops)
{

}

int		main(int ac, char **av)
{
	t_opts	opts;
	t_champs	*c;

	if (ac < 2)
		display_usage();
	opts = parse_opts(av + 1);
	c = NULL;
	register_champs(c);

	while (1)
	{

		if (!corewar_game())
			display_result();
	}
	return (0);
}
