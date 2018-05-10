/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etieberg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 19:03:36 by etieberg          #+#    #+#             */
/*   Updated: 2018/05/10 19:03:45 by etieberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void    free_vm(t_vm *vm, t_opts opts)
{
	unsigned int    i;

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
