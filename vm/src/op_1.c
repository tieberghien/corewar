/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syboeuf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 16:50:19 by syboeuf           #+#    #+#             */
/*   Updated: 2018/05/10 18:20:33 by syboeuf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	verb_adv(t_vm *vm, t_process *process, int l)
{
	int	len;
	int	i;

	len = l;
	i = 0;
	ft_printf("ADV %d (", len);
	if (process->pc == 0)
		ft_putstr("0x");
	ft_printf("%#.4x -> ", process->pc);
	if (process->pc + len == 0)
		ft_putstr("0x");
	ft_printf("%#.4x) ", process->pc + len);
	while (i < len)
	{
		ft_printf("%.2hhx ", vm->map[(process->pc + i) % MEM_SIZE]);
		i++;
	}
	ft_putchar('\n');
}

int		aff(t_vm *vm, t_op *op, t_process *process)
{
	if (((op->ocp & PARAM_C) >> 6) != 1 || ((op->ocp & PARAM_B) >> 4) != 0
			|| ((op->ocp & PARAM_A) >> 2) != 0)
		return (0);
	vm->map[0] = vm->map[0];
	if (process->registre[op->params[0] - 1] == 0)
		process->carry = 1;
	else
		process->carry = 0;
	return (process->carry);
}

int		op_lfork(t_vm *vm, t_op *op, t_process *process)
{
	t_process	*new;

	if (!(new = ft_memalloc(sizeof(t_process))))
		return (-1);
	*new = *process;
	if (op->params[0] == 0)
		new->pc = (process->pc + 3) % MEM_SIZE;
	else
		new->pc = (op->params[0] + process->pc) % MEM_SIZE;
	new->next = *(vm->process);
	*(vm->process) = new;
	vm->ping++;
	new->number = vm->ping;
	return (0);
}

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

int		op_xor(t_vm *vm, t_op *op, t_process *process)
{
	int par_a;
	int par_b;
	int err;

	vm->map[0] = vm->map[0];
	if (((op->ocp & PARAM_C) >> 6) == 0
			|| ((op->ocp & PARAM_B) >> 4) == 0
			|| ((op->ocp & PARAM_A) >> 2) != 1)
		return (0);
	if ((err = (((op->ocp & PARAM_C)) >> 6) == 1)
			&& (op->params[0] > REG_NUMBER || op->params[0] < 1))
		return (process->carry);
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
	if (process->registre[op->params[2] - 1] == 0)
		process->carry = 1;
	else
		process->carry = 0;
	return (process->carry);
}

int		op_or(t_vm *vm, t_op *op, t_process *process)
{
	int par_a;
	int par_b;
	int err;

	vm->map[0] = vm->map[0];
	if (((op->ocp & PARAM_C) >> 6) == 0
			|| ((op->ocp & PARAM_B) >> 4) == 0
			|| ((op->ocp & PARAM_A) >> 2) != 1)
		return (0);
	if ((err = (((op->ocp & PARAM_C)) >> 6) == 1)
			&& (op->params[0] > REG_NUMBER || op->params[0] < 1))
		return (process->carry);
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
	if (process->registre[op->params[2] - 1] == 0)
		process->carry = 1;
	else
		process->carry = 0;
	return (process->carry);
}

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

int		op_fork(t_vm *vm, t_op *op, t_process *process)
{
	t_process	*new;

	if (!(new = ft_memalloc(sizeof(t_process))))
		return (-1);
	*new = *process;
	if (op->params[0] == 0)
		new->pc = (process->pc + 3) % MEM_SIZE;
	else
		new->pc = res_add(op->params[0], process->pc) % MEM_SIZE;
	new->next = *(vm->process);
	*(vm->process) = new;
	vm->ping++;
	new->number = vm->ping;
	return (0);
}

int		sti2(t_op *op, int *k)
{
	if (((op->ocp & PARAM_C) >> 6) != 1
			|| ((op->ocp & PARAM_B) >> 4) == 0
			|| ((op->ocp & PARAM_A) >> 2) == 0
			|| ((op->ocp & PARAM_A) >> 2) == 3)
		return (0);
	if (op->params[0] <= 0 || op->params[0] > REG_NUMBER)
		return (0);
	if ((*k = (((op->ocp & PARAM_B)) >> 4) == 1)
			&& (op->params[1] > REG_NUMBER || op->params[1] < 1))
		return (0);
	return (1);
}

int		sti(t_vm *vm, t_op *op, t_process *process)
{
	unsigned int	par_a;
	unsigned int	par_b;
	unsigned char	*idx_val;
	int				k;

	if (sti2(op, &k) == 0)
		return (0);
	if (k == 3)
		par_a = (short)op->params[1];
	else
		par_a = (k == 1) ? process->registre[op->params[1] - 1] : op->params[1];
	if (((k = ((op->ocp & PARAM_A) >> 2)) == 1)
			&& (op->params[2] > REG_NUMBER || op->params[2] < 1))
		return (process->carry);
	par_b = (k == 1) ? process->registre[op->params[2] - 1] : op->params[2];
	tointhex(process->registre[op->params[0] - 1], &idx_val);
	par_a = res_add(par_a + par_b, process->pc);
	if (!idx_val)
		return (process->carry);
	k = -1;
	while (++k < 4)
		vm->map[(par_a + k) % MEM_SIZE] = idx_val[k];
	ft_memdel((void**)&idx_val);
	return (process->carry);
}

int		zjmp(t_vm *vm, t_op *op, t_process *process)
{
	unsigned int i;

	vm->map[0] = vm->map[0];
	i = 0;
	if (process->carry == 1)
	{
		process->pc = res_add(op->params[0], process->pc);
		return (process->carry);
	}
	verb_adv(vm, process, 3);
	process->pc = (process->pc + 3) % MEM_SIZE;
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
			//verbose_one(*(vm->champs + i));
			vm->last_live = vm->champs[i].player_id;
			return (process->carry);
		}
		i++;
	}
	return (process->carry);
}
