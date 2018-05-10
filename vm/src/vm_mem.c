/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_mem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syboeuf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 16:39:56 by syboeuf           #+#    #+#             */
/*   Updated: 2018/05/10 16:45:32 by syboeuf          ###   ########.fr       */
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

void	p_turn(t_vm *vm, t_process *process)
{
	int j;
	int k;

	j = 0;
	k = 0;
	if (process->op.dur > 1)
		process->op.dur--;
	else if (process->op.dur == 1)
	{
		k = 0;
		process->op.dur--;
		if (process->op.op_code == 9 || process->op.op_code == 15
				|| process->op.op_code == 12 || process->op.op_code == 1)
		{
			if (process->op.op_code == 1)
				process->live++;
			j = save_op_spec(process, vm);
		}
		else if (process->op.op_code > 1 && process->op.op_code <= 16)
		{
			process->op.ocp = vm->map[(process->pc + 1) % MEM_SIZE];
			j = save_op(process, vm);
		}
		if (process->op.op_code != 9 && process->op.op_code != 3
				&& process->op.op_code != 11)
			verb_adv(vm, process, j);
		if (process->op.op_code > 0 && process->op.op_code <= 16)
			k = g_op[process->op.op_code - 1](vm, &(process->op), process);
		if (process->op.op_code != 9 &&
				(process->op.op_code == 3 || process->op.op_code == 11))
			verb_adv(vm, process, j);
		if (process->op.op_code != 9 && k >= 0)
			process->pc = (process->pc + j) % MEM_SIZE;
		else if (k < 0)
			process->pc = (process->pc + 2) % MEM_SIZE;
	}
	else if (process->op.dur <= 0)
	{
		if (vm->map[process->pc] > 0 && vm->map[process->pc] <= 16)
		{
			process->op = g_optab[vm->map[process->pc] - 1];
			process->op.dur--;
		}
		else
			process->pc = (process->pc + 1) % MEM_SIZE;
	}
}

int		start_game(t_vm *vm)
{
	int				i;
	t_process		*process;
	int				check;
	unsigned int	tot_cycle;

	check = 0;
	vm->live_num = 0;
	tot_cycle = 0;
	while (1)
	{
		vm->cycle = vm->next_cycle_group;
		while (vm->cycle > 0)
		{
			ft_printf("It is now cycle %d\n", tot_cycle + 1);
			i = -1;
			process = *(vm->process);
			while (process)
			{
				p_turn(vm, process);
				process = process->next;
			}
			tot_cycle++;
			vm->c = tot_cycle;
			if (vm->opts->s_cycles != 0 && tot_cycle >= vm->opts->s_cycles)
				return (-6);
			vm->cycle--;
		}
		if (check_alive(vm->process, 0) < 0)
			return (-1);
		check++;
		if (check >= MAX_CHECKS || vm->live_num >= NBR_LIVE)
		{
			vm->next_cycle_group -= CYCLE_DELTA;
			ft_printf("Cycle to die is now %d\n", vm->next_cycle_group);
			check = 0;
		}
		if (vm->next_cycle_group < 0)
			return (1);
		vm->live_num = 0;
	}
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
		j = 0;
		pos = i * gap;
		process = ft_memalloc(sizeof(t_process));
		process->pc = pos;
		process->carry = 0;
		process->live = 0;
		process->champ = i;
		init_reg(champs, i, process);
		process->op = g_optab[16];
		vm->ping++;
		process->number = vm->ping;
		process->next = *(vm->process);
		*(vm->process) = process;
		vm->last_live = champs[i].player_id;
		j = -1;
		while (++j < (int)champs[i].size)
		{
			vm->map[j + pos] = champs[i].instructions[j];
		}
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
	if (install_champion(champs, opts, vm))
		return (ft_printf("Error, the map is not initilisated\n"));
	if (start_game(vm) < -5)
	{
		print_vm_mem(vm);
		check_alive(vm->process, 1);
		return (1000);
	}
	else
	{
		i = 0;
		while (champs[i].player_id != vm->last_live)
			i++;
		verbose_zero(champs + i);
		check_alive(vm->process, 1);
	}
	return (0);
}
