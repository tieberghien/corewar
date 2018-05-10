/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_extra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syboeuf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 16:18:03 by syboeuf           #+#    #+#             */
/*   Updated: 2018/05/10 17:44:14 by syboeuf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int				res_add(unsigned int param, int pc)
{
	int hello;

	hello = (short)param;
	hello = (hello >= 0) ? hello % IDX_MOD : -(-hello % IDX_MOD);
	hello = pc + hello;
	hello = (hello >= 0) ? hello % MEM_SIZE : MEM_SIZE - (-hello % MEM_SIZE);
	return (hello);
}

void			ft_procdel(t_process **op)
{
	if (!*op)
		return ;
	free(*op);
	*op = NULL;
}

unsigned int	init_check(t_process **tmp, t_process **tmp2,
		t_process **process, int flag)
{
	unsigned int i;

	i = 0;
	if ((*tmp)->live == 0 || flag == 1)
	{
		if (!(*tmp2))
			(*process) = (*tmp)->next;
		else
			(*tmp2)->next = (*tmp)->next;
		ft_procdel(tmp);
		if (!(*tmp2))
			(*tmp) = *process;
		else
			(*tmp) = (*tmp2)->next;
	}
	else
	{
		(*tmp)->live = 0;
		*tmp2 = *tmp;
		(*tmp) = (*tmp)->next;
		i++;
	}
	return (i);
}

int				check_alive(t_process **process, int flag)
{
	unsigned int	i;
	t_process		*tmp;
	t_process		*tmp2;

	i = 0;
	if (!*process)
		return (-1);
	tmp = *process;
	tmp2 = NULL;
	while (tmp != NULL)
		i += init_check(&tmp, &tmp2, process, flag);
	return ((i > 0) ? 1 : -1);
}

void			tointhex(unsigned long int num, unsigned char **tmp)
{
	unsigned int	total;
	unsigned int	cpy;
	unsigned char	*new;
	int				i;

	i = -1;
	if (!(new = (unsigned char*)malloc(sizeof(unsigned char) * 4)))
		return ;
	total = 256 * 256 * 256;
	while (++i < 4)
	{
		cpy = num / total;
		new[i] = (unsigned char)(cpy % 256);
		total /= 256;
	}
	*tmp = new;
}
