/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 15:59:20 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/04/14 14:50:25 by etieberg         ###   ########.fr       */
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
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0, 1},
};

static int		get_opname(char *line, t_ops *ops)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (line[i] != ' ' && line[i] != '\t' && line[i] != '%' && line[i])
		i++;
	if (!line[i])
		return (-1);
	while (j < 16)
	{
		if (!ft_strncmp(line, g_op_tab[j].name, i))
		{
			if (!(ops->name = ft_strsub(line, 0, i)))
				return (-1);
			return (j);
		}
		j++;
	}
	return (-1);
}

static int	go_next_param(char *line)
{
	int	i;
	
	i = 0;
	while (line[i])
	{
		if (line[i] == ',')
		{
			i++;
			while (line[i] == '\t' || line[i] == ' ')
				i++;
			return (i);
		}
		i++;
	}
	return (-1);
}

static int	setup_filldata(t_ops *ops, char *line, int index)
{
	int	i;

	ops->lc = 0;
	ops->pc = (g_op_tab[index].ocp) ? 2 : 1;
	ops->small = (g_op_tab[index].small) ? 2 : 4;
	write_to_data(ops->data, g_op_tab[index].op_code, 0, 1);
	i = ft_strlen(ops->name);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);
}

static int	fill_opdata(t_ops *ops, char *line, int index)
{
	int	count;
	int	ret;
	int	i;
	int	cb;

	count = -1;
	cb = 0;
	i = setup_filldata(ops, line, index);
	while (++count < g_op_tab[index].argc)
	{
		ret = ops->pc;
		if (g_op_tab[index].params[count] & T_REG)
			fill_reg(line + i, ops, count, &cb);
		if (g_op_tab[index].params[count] & T_DIR)
			fill_index(line + i, ops, count, &cb);
		if (g_op_tab[index].params[count] & T_IND)
			fill_value(line + i, ops, count, &cb);
		if (ret == ops->pc || (count + 1 < g_op_tab[index].argc &&
		(ret = go_next_param(line + i)) == -1))
			return (ret);
		i += ret;
	}
	if (g_op_tab[index].ocp)
		write_to_data(ops->data, cb, 1, 1);
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
		fill_opdata(*ops, line, i);
		(*ops)->end_addr = (*ops)->pc;
		return (1);
	}
	tmp = *ops;
	while (tmp->nxt != NULL)
		tmp = tmp->nxt;
	if (!(new = malloc(sizeof(t_ops))) || (i = get_opname(line, new)) == -1)
		return (0);
	new->nxt = NULL;
	fill_opdata(new, line, i);
	tmp->nxt = new;
	new->end_addr = tmp->end_addr + new->pc;
	return (1);
}
