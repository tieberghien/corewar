/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syboeuf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 18:22:50 by syboeuf           #+#    #+#             */
/*   Updated: 2018/05/10 18:28:23 by syboeuf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		op2(t_op *op, int *err)
{
	if (((op->ocp & PARAM_C) >> 6) == 0
			|| ((op->ocp & PARAM_B) >> 4) == 0
			|| ((op->ocp & PARAM_A) >> 2) != 1)
		return (0);
	if ((*err = (((op->ocp & PARAM_C)) >> 6) == 1)
			&& (op->params[0] > REG_NUMBER || op->params[0] < 1))
		return (0);
	return (1);
}

int		op_xor(t_vm *vm, t_op *op, t_process *process)
{
	int par_a;
	int par_b;
	int err;

	vm->map[0] = vm->map[0];
	if (op2(op, &err) == 0)
		return (0);
	if (err == 3)
		par_a = res_add(op->params[0], process->pc);
	else
		par_a = (err == 1) ?
			process->registre[op->params[0] - 1] : op->params[0];
	if (((err = ((op->ocp & PARAM_B) >> 4)) == 1)
			&& (op->params[1] > REG_NUMBER || op->params[1] < 1))
		return (process->carry);
	if (err == 3)
		par_b = res_add(op->params[1], process->pc);
	else
		par_b = (err == 1) ?
			process->registre[op->params[1] - 1] : op->params[1];
	if (op->params[2] > REG_NUMBER || op->params[2] < 1)
		return (process->carry);
	process->registre[op->params[2] - 1] = par_a ^ par_b;
	process->carry = (process->registre[op->params[2] - 1] == 0) ? 1 : 0;
	return (process->carry);
}

int		op_or(t_vm *vm, t_op *op, t_process *process)
{
	int par_a;
	int par_b;
	int err;

	vm->map[0] = vm->map[0];
	if (op2(op, &err) == 0)
		return (0);
	if (err == 3)
		par_a = res_add(op->params[0], process->pc);
	else
		par_a = (err == 1) ?
			process->registre[op->params[0] - 1] : op->params[0];
	if (((err = ((op->ocp & PARAM_B) >> 4)) == 1)
			&& (op->params[1] > REG_NUMBER || op->params[1] < 1))
		return (process->carry);
	if (err == 3)
		par_b = res_add(op->params[1], process->pc);
	else
		par_b = (err == 1) ?
			process->registre[op->params[1] - 1] : op->params[1];
	if (op->params[2] > REG_NUMBER || op->params[2] < 1)
		return (process->carry);
	process->registre[op->params[2] - 1] = par_a | par_b;
	process->carry = (process->registre[op->params[2] - 1] == 0) ? 1 : 0;
	return (process->carry);
}

int		op_and(t_vm *vm, t_op *op, t_process *process)
{
	int par_a;
	int par_b;
	int err;

	vm->map[0] = vm->map[0];
	if (op2(op, &err) == 0)
		return (0);
	if (err == 3)
		par_a = res_add(op->params[0], process->pc);
	else
		par_a = (err == 1) ?
			process->registre[op->params[0] - 1] : op->params[0];
	if (((err = ((op->ocp & PARAM_B) >> 4)) == 1)
			&& (op->params[1] > REG_NUMBER || op->params[1] < 1))
		return (process->carry);
	if (err == 3)
		par_b = res_add(op->params[1], process->pc);
	else
		par_b = (err == 1) ?
			process->registre[op->params[1] - 1] : op->params[1];
	if (op->params[2] > REG_NUMBER || op->params[2] < 1)
		return (process->carry);
	process->registre[op->params[2] - 1] = par_a & par_b;
	process->carry = (process->registre[op->params[2] - 1] == 0) ? 1 : 0;
	return (process->carry);
}

int		sub(t_vm *vm, t_op *op, t_process *process)
{
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
	process->registre[op->params[2] - 1] = process->registre[op->params[0] - 1]
		- process->registre[op->params[1] - 1];
	if (process->registre[op->params[2] - 1] == 0)
		process->carry = 1;
	else
		process->carry = 0;
	return (process->carry);
}
