/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syboeuf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 18:32:36 by syboeuf           #+#    #+#             */
/*   Updated: 2018/05/10 18:58:24 by syboeuf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	verb_adv(t_vm *vm, t_process *process, int l)
{
	int len;
	int i;

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
