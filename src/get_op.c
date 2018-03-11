/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 15:59:20 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/03/11 23:07:46 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_op    g_op_tab[16] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0, 1},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0, 1},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0, 1},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0, 1},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0, 1},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0, 1},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0, 1},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1, 0},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1, 0},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0, 1},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1, 0},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
};

int		get_opname(char *line, t_ops *ops)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	ops->labels = NULL;
	ops->lc = 0;
	while (line[i] != ' ' && line[i] != '\t' && line[i])
		i++;
	if (!line[i])
		return (-1);
	while (j < 16)
	{
		if (!ft_strncmp(line, g_op_tab[j].name, i))
		{
			ops->name = ft_strsub(line, 0, i);
			return (i);
		}
		j++;
	}
	return (-1);
}

void	get_op_addr(t_ops *ops, t_ops *prev)
{
	ops->end_addr = ops->addr;
	if (prev)
	{
		ops->end_addr += prev->end_addr;
		ops->addr = prev->end_addr;
	}
	else 
		ops->addr = 0;
}

int	fill_opdata(t_op *ops, char *line, int i)
{
	int	count;
	int	ret;
	int	pc;

	pc = 0;
	count = -1;
	while (++count < g_op_tab[i].argc)
	{
		ret = pc;
		if (g_op_tab[i].params[count] & T_REG)
			pc += fill_reg(line + i, ops->data) 
		if (g_op_tab[i].params[count] & T_DIR)
			pc += fill_index(line + i, ops->data, (g_op_tab[i].small) ? 2 : 4);
		if (g_op_tab[i].params[count] & T_IND)
			pc += fill_value(line + i, ops->data);
		if (ret == pc || (ret = go_next_param(line + i)) == -1)
		   return (ret);	
		i += ret;
	}
	ops->addr = (g_op_tab[i].ocp) ? pc + 2 : pc + 1;
	return (1);
}

int	get_op(char *line, t_ops **ops)
{
	t_ops 	*tmp;
	t_ops	*new;	
	int		i;

	if (*ops == NULL)
	{
		if (!(*ops = malloc(sizeof(t_ops))) || (i = get_opname(line, *ops)) == -1)
			return (0);
		(*ops)->nxt = NULL;
		get_op_addr(*ops, NULL);
		fill_in_opdata(*ops, line, i);
		return (1);
	}
	tmp = *ops;
	while (tmp->nxt != NULL)
		tmp = tmp->nxt;
	if (!(new = malloc(sizeof(t_ops))) || (i = get_opname(line, new)) == -1)
		return (0);
	new->nxt = NULL;
	get_op_addr(new, tmp);
	tmp->nxt = new;
	fill_in_opdata(*ops, line, i);
	return (1);
}
