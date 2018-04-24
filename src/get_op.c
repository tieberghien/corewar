/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 15:59:20 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/04/24 17:02:55 by etieberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	get_opname(char *line, t_ops *ops)
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

static int	next_param(char *line)
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

static char	*is_type(char *type)
{
	if (!type)
		return (NULL);
	else if (type[0] == 'r')
		return ("register");
	else if (type[0] == '%')
		return ("direct");
	else if (ft_isdigit(type[0]) || type[0] == '-' || type[0] == ':')
		return ("indirect");
	return (NULL);
}

static void	fill_opdata(t_ops *ops, char *l, int index)
{
	int	c;
	int	ret;
	int	i;
	int	cb;

	c = -1;
	cb = 0;
	i = setup_filldata(ops, l, index);
	while (++c < g_op_tab[index].argc)
	{
		ret = ops->pc;
		if (g_op_tab[index].params[c] & T_REG)
			fill_reg(l + i, ops, c, &cb);
		if (g_op_tab[index].params[c] & T_DIR)
			fill_index(l + i, ops, c, &cb);
		if (g_op_tab[index].params[c] & T_IND)
			fill_value(l + i, ops, c, &cb);
		if (ret == ops->pc)
			return_invparams(c, is_type(l + i), g_op_tab[index].name);
		if ((c + 1 < g_op_tab[index].argc && (ret = next_param(l + i)) == -1))
			return_failure(PARAMS_NO, g_op_tab[index].name);
		i += ret;
	}
	if (g_op_tab[index].ocp)
		write_to_data(ops->data, cb, 1, 1);
}

int			get_op(char *line, t_ops **ops)
{
	t_ops	*tmp;
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
