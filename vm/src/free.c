/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etieberg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 19:03:36 by etieberg          #+#    #+#             */
/*   Updated: 2018/05/10 19:22:49 by etieberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	cycle_to_die(t_opts *opts, unsigned int tot_cycle, int flag)
{
	if (opts->verbosity == 1)
	{
		if (flag == 1)
			ft_printf("It is now cycle %d\n", tot_cycle + 1);
		else if (flag == 2)
			ft_printf("Cycle to die is now %d\n", tot_cycle);
	}
}

void	free_vm(t_vm *vm, t_opts opts)
{
	unsigned int i;

	i = 0;
	if (vm)
	{
		free(vm->map);
		while (i < opts.n_players)
		{
			free(vm->champs[i].name);
			free(vm->champs[i].comment);
			free(vm->champs[i].instructions);
			i++;
		}
	}
}
