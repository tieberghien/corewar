/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_mem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syboeuf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 16:39:56 by syboeuf           #+#    #+#             */
/*   Updated: 2018/05/10 20:32:29 by etieberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	init_reg(t_champs *champs, int player, t_process *process)
{
	int i;

	i = 0;
	process->registre[0] = champs[player].player_id;
	while (++i < REG_NUMBER)
		process->registre[i] = 0;
}

void	init_process(t_process *process, int i, int pos)
{
	process->pc = pos;
	process->carry = 0;
	process->live = 0;
	process->champ = i;
}

int		install_champion(t_champs *champs, t_opts *opts, t_vm *vm)
{
	int			i;
	int			gap;
	int			pos;
	int			j;
	t_process	*process;

	i = -1;
	gap = (MEM_SIZE / opts->n_players);
	while ((unsigned int)++i < opts->n_players)
	{
		pos = i * gap;
		process = ft_memalloc(sizeof(t_process));
		init_process(process, i, pos);
		init_reg(champs, i, process);
		process->op = g_optab[16];
		vm->ping++;
		process->number = vm->ping;
		process->next = *(vm->process);
		*(vm->process) = process;
		vm->last_live = champs[i].player_id;
		j = -1;
		while (++j < (int)champs[i].size)
			vm->map[j + pos] = champs[i].instructions[j];
	}
	return (0);
}

int		before_start_game(t_vm *vm, t_opts *opts, t_champs *champs)
{
	int i;

	i = 0;
	if (install_champion(champs, opts, vm))
		return (ft_printf("Error, the map is not initilisated\n"));
	if (start_game(vm, opts) < -5)
	{
		print_vm_mem(vm);
		check_alive(vm->process, 1);
		return (1000);
	}
	else
	{
		while (champs[i].player_id != vm->last_live)
			i++;
		verbose_zero(champs + i);
		check_alive(vm->process, 1);
	}
	return (0);
}

int		init_vm(t_champs *champs, t_opts *opts, t_vm *vm)
{
	int			i;
	t_op		*op;
	t_process	*proc;

	op = NULL;
	vm->cycle = CYCLE_TO_DIE;
	vm->ping = 0;
	vm->next_cycle_group = CYCLE_TO_DIE;
	vm->opts = opts;
	vm->champs = champs;
	proc = NULL;
	vm->process = &proc;
	if (!(vm->map = (unsigned char*)malloc(sizeof(unsigned char) * MEM_SIZE)))
		return (-1);
	i = -1;
	while (++i < MEM_SIZE)
	{
		vm->map[i] = 0;
	}
	before_start_game(vm, opts, champs);
	return (0);
}
