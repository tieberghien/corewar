/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 15:59:20 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/04/30 13:37:47 by slynn-ev         ###   ########.fr       */
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

static int		get_first_op(char *line, t_ops **ops)
{
	int	i;

	if (!(*ops = malloc(sizeof(t_ops))))
		return (0);
	if ((i = get_opname(line, *ops)) == -1)
		return (0);
	(*ops)->nxt = NULL;
	fill_opdata(*ops, line, i);
	(*ops)->end_addr = (*ops)->pc;
	return (1);
}

int			get_op(char *line, t_ops **ops)
{
	t_ops	*tmp;
	t_ops	*new;
	int		i;

	if (*ops == NULL)
		return (get_first_op(line, ops));
	tmp = *ops;
	while (tmp->nxt != NULL)
		tmp = tmp->nxt;
	if (!(new = malloc(sizeof(t_ops))))
		return (0);
	if ((i = get_opname(line, new)) == -1)
		return (0);
	new->nxt = NULL;
	fill_opdata(new, line, i);
	tmp->nxt = new;
	new->end_addr = tmp->end_addr + new->pc;
	return (1);
}
