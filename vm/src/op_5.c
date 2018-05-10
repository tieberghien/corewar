/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_5.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syboeuf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 18:36:35 by syboeuf           #+#    #+#             */
/*   Updated: 2018/05/10 23:05:35 by gficara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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
	if (vm->opts->verbosity == 1)
		verb_adv(vm, process, 3);
	process->pc = (process->pc + 3) % MEM_SIZE;
	return (process->carry);
}
