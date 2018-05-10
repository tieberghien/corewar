/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_mem2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etieberg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 20:23:21 by etieberg          #+#    #+#             */
/*   Updated: 2018/05/10 21:34:23 by etieberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	p_turn2(t_vm *vm, t_process *process, int k, int j)
{
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

void	p_turn(t_vm *vm, t_process *process)
{
	int j;
	int k;

	j = 0;
	k = 0;
	if (process->op.dur > 1)
		process->op.dur--;
	else if (process->op.dur == 1)
		p_turn2(vm, process, k, j);
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

int		start_game2(t_vm *vm, t_opts *opts)
{
	t_process	*process;

	vm->cycle = vm->next_cycle_group;
	while (vm->cycle > 0)
	{
		cycle_to_die(opts, vm->tot_cycle, 1);
		process = *(vm->process);
		while (process)
		{
			p_turn(vm, process);
			process = process->next;
		}
		vm->tot_cycle++;
		if (vm->opts->s_cycles != 0 && vm->tot_cycle >= vm->opts->s_cycles)
			return (-6);
		vm->cycle--;
	}
	return (0);
}

int		start_game(t_vm *vm, t_opts *opts)
{
	int	check;

	check = 0;
	vm->live_num = 0;
	vm->tot_cycle = 0;
	while (1)
	{
		if (start_game2(vm, opts) == -6)
			return (-6);
		if (check_alive(vm->process, 0) < 0)
			return (-1);
		check++;
		if (check >= MAX_CHECKS || vm->live_num >= NBR_LIVE)
		{
			vm->next_cycle_group -= CYCLE_DELTA;
			cycle_to_die(opts, vm->next_cycle_group, 2);
			check = 0;
		}
		if (vm->next_cycle_group < 0)
			return (1);
		vm->live_num = 0;
	}
}
