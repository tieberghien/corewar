/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syboeuf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 18:29:35 by syboeuf           #+#    #+#             */
/*   Updated: 2018/05/10 18:31:38 by syboeuf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		lldi2(t_op *op, int *k)
{
	if (((op->ocp & PARAM_C) >> 6) == 0
			|| ((op->ocp & PARAM_B) >> 4) == 0
			|| ((op->ocp & PARAM_B) >> 4) == 3
			|| ((op->ocp & PARAM_A) >> 2) != 1)
		return (0);
	if (op->params[2] <= 0 || op->params[2] > REG_NUMBER)
		return (0);
	if ((*k = (((op->ocp & PARAM_C)) >> 6) == 1) &&
			(op->params[0] > REG_NUMBER || op->params[0] < 1))
		return (0);
	return (1);
}

int		lldi(t_vm *vm, t_op *op, t_process *process)
{
	int par_a;
	int par_b;
	int k;

	vm->map[0] = vm->map[0];
	if (lldi2(op, &k) == 0)
		return (0);
	if (k == 3)
		par_a = (short)op->params[0];
	else
		par_a = (k == 1) ? process->registre[op->params[0] - 1] : op->params[0];
	if ((k = (((op->ocp & PARAM_B)) >> 4) == 1)
			&& (op->params[1] > REG_NUMBER || op->params[1] < 1))
		return (process->carry);
	par_b = (k == 1) ?
		process->registre[op->params[1] - 1] : (short)op->params[1];
	process->registre[op->params[2] - 1] = toint(vm, par_a + par_b, 4);
	if (process->registre[op->params[2] - 1] == 0)
		process->carry = 1;
	else
		process->carry = 0;
	return (process->carry);
}

int		lld(t_vm *vm, t_op *op, t_process *process)
{
	if (((op->ocp & PARAM_C) >> 6) < 2
			|| ((op->ocp & PARAM_B) >> 4) > 1
			|| ((op->ocp & PARAM_B) >> 4) != 1
			|| ((op->ocp & PARAM_A) >> 2) != 0)
		return (0);
	vm->map[0] = vm->map[0];
	if (op->params[1] > 0 && op->params[1] <= REG_NUMBER)
		process->registre[op->params[1] - 1] = op->params[0];
	else
		return (0);
	if (op->params[0] == 0)
		process->carry = 1;
	else
		process->carry = 0;
	return (process->carry);
}

int		ldi2(t_op *op, int *k)
{
	if (((op->ocp & PARAM_C) >> 6) == 0 || ((op->ocp & PARAM_B) >> 4) == 0
			|| ((op->ocp & PARAM_B) >> 4) == 3
			|| ((op->ocp & PARAM_A) >> 2) != 1)
		return (0);
	if (op->params[2] <= 0 || op->params[2] > REG_NUMBER)
		return (0);
	if ((*k = (((op->ocp & PARAM_C)) >> 6) == 1)
			&& (op->params[0] > REG_NUMBER || op->params[0] < 1))
		return (0);
	return (1);
}

int		ldi(t_vm *vm, t_op *op, t_process *process)
{
	int par_a;
	int par_b;
	int k;

	vm->map[0] = vm->map[0];
	if (ldi2(op, &k) == 0)
		return (0);
	if (k == 3)
		par_a = (short)op->params[0];
	else
		par_a = (k == 1) ? process->registre[op->params[0] - 1] : op->params[0];
	if ((k = (((op->ocp & PARAM_B)) >> 4) == 1)
			&& (op->params[1] > REG_NUMBER || op->params[1] < 1))
		return (process->carry);
	par_b = (k == 1) ?
		process->registre[op->params[1] - 1] : (short)op->params[1];
	process->registre[op->params[2] - 1] = toint(vm,
			res_add(par_a + par_b, process->pc), 4);
	if (process->registre[op->params[2] - 1] == 0)
		process->carry = 1;
	else
		process->carry = 0;
	return (process->carry);
}
