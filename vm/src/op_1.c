/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syboeuf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 16:50:19 by syboeuf           #+#    #+#             */
/*   Updated: 2018/05/10 19:24:42 by etieberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		add(t_vm *vm, t_op *op, t_process *process)
{
	unsigned int par_a;
	unsigned int par_b;

	vm->map[0] = vm->map[0];
	if (((op->ocp & PARAM_C) >> 6) != 1
			|| ((op->ocp & PARAM_B) >> 4) != 1
			|| ((op->ocp & PARAM_A) >> 2) != 1)
		return (0);
	if (op->params[0] <= 0 || op->params[0] > REG_NUMBER)
		return (0);
	if (op->params[1] <= 0 || op->params[1] > REG_NUMBER)
		return (0);
	if (op->params[2] <= 0 || op->params[2] > REG_NUMBER)
		return (0);
	par_a = process->registre[op->params[1] - 1];
	par_b = process->registre[op->params[0] - 1];
	process->registre[op->params[2] - 1] = par_a + par_b;
	if (process->registre[op->params[2] - 1] == 0)
		process->carry = 1;
	else
		process->carry = 0;
	return (process->carry);
}

int		st2(t_process *process, t_op *op, t_vm *vm)
{
	unsigned char	*idx_val;
	int				k;

	tointhex(process->registre[op->params[0] - 1], &idx_val);
	if (!idx_val)
		return (0);
	k = -1;
	while (++k < 4)
		vm->map[(op->params[1] + k) % MEM_SIZE] = idx_val[k];
	ft_memdel((void**)&idx_val);
	return (1);
}

int		st(t_vm *vm, t_op *op, t_process *process)
{
	if (((op->ocp & PARAM_C) >> 6) != 1
			|| ((op->ocp & PARAM_B) >> 4) == 2
			|| ((op->ocp & PARAM_B) >> 4) == 0
			|| ((op->ocp & PARAM_A) >> 2) != 0)
		return (0);
	if (((op->ocp & PARAM_B) >> 4) == 1)
	{
		if ((op->params[1] <= 0 || op->params[1] > REG_NUMBER)
				|| (op->params[0] <= 0 || op->params[0] > REG_NUMBER))
			return (0);
		process->registre[op->params[1] - 1] =
			process->registre[op->params[0] - 1];
	}
	else
	{
		if ((op->params[0] <= 0 || op->params[0] > REG_NUMBER))
			return (0);
		op->params[1] = res_add(op->params[1], process->pc);
		if (st2(process, op, vm) == 0)
			return (process->carry);
	}
	return (process->carry);
}

int		ld(t_vm *vm, t_op *op, t_process *process)
{
	if (((op->ocp & PARAM_C) >> 6) < 2
			|| ((op->ocp & PARAM_B) >> 4) != 1
			|| ((op->ocp & PARAM_A) >> 2) != 0)
		return (0);
	vm->map[0] = vm->map[0];
	if (op->params[1] > 0 && op->params[1] <= REG_NUMBER)
	{
		if (((op->ocp & PARAM_C) >> 6) == 2)
			process->registre[op->params[1] - 1] = op->params[0];
		else
			process->registre[op->params[1] - 1] = toint(vm,
					res_add(op->params[0], process->pc), 4);
	}
	else
		return (0);
	if (op->params[0] == 0)
		process->carry = 1;
	else
		process->carry = 0;
	return (process->carry);
}

int		live(t_vm *vm, t_op *op, t_process *process)
{
	unsigned int i;

	process->champ = process->champ;
	i = 0;
	vm->live_num++;
	while (i < vm->opts->n_players)
	{
		if (op->params[0] == vm->champs[i].player_id)
		{
			verbose_one(*(vm->champs + i));
			vm->last_live = vm->champs[i].player_id;
			return (process->carry);
		}
		i++;
	}
	return (process->carry);
}
