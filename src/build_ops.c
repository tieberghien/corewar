/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 19:44:10 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/04/18 15:50:00 by etieberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	check_chars(char *line)
{
	while (*line)
	{
		if (!ft_strrchr(LABEL_CHARS, *line))
			return (0);
		line++;
	}
	return (1);
}

int	get_address(t_ops *ops)
{
	t_ops	*tmp;

	tmp = ops;
	if (!tmp)
		return (0);
	while (tmp->nxt)
		tmp = tmp->nxt;
	return (tmp->end_addr);
}

int	match_labels(t_label *l, t_ops *ops)
{
	int		i;
	t_label *tmp;

	while (ops)
	{
		i = -1;
		while (++i < ops->lc)
		{
			tmp = l;
			while (tmp)
			{
				if (!ft_strcmp(tmp->name, ops->labels[i]))
				{
					write_to_data(ops->data, tmp->address -
						(ops->end_addr - ops->pc), ops->put[i][0], ops->put[i][1]);
					break ;
				}
				tmp = tmp->nxt;
			}
			if (!tmp)
				return (0);
		}
		ops = ops->nxt;
	}
	return (1);
}

int	add_label(t_label **l, char *line, int address, int end)
{
	t_label	*tmp;
	t_label	*new;

	if (*l == NULL)
	{
		if (!(*l = malloc(sizeof(t_label))))
			return (0);
		(*l)->name = ft_strsub(line, 0, end);
		(*l)->address = address;
		(*l)->nxt = NULL;
		return (check_chars((*l)->name));
	}
	tmp = *l;
	while (tmp->nxt != NULL)
		tmp = tmp->nxt;
	if (!(new = malloc(sizeof(t_label))))
		return (0);
	new->name = ft_strsub(line, 0, end);
	new->address = address;
	new->nxt = NULL;
	tmp->nxt = new;
	return (check_chars(new->name));
}

int	build_operations(t_am *a, t_label **l, t_ops **ops)
{
	int		i;
	int		j;
	int		label_line;

	i = a->eoc;
	while (++i < a->lc)
	{
		label_line = 0;
		j = -1;
		while (a->lines[i][++j] != ' ' && a->lines[i][j] != '\t' 
				&& a->lines[i][j] != '%' && a->lines[i][j])
			if (a->lines[i][j] == ':')
			{
				label_line = 1;
				if (!add_label(l, a->lines[i], get_address(*ops), j))
					return (0);
				while (a->lines[i][++j] == ' ' || a->lines[i][j] == '\t')
					;
				if (a->lines[i][j] && !get_op(a->lines[i] + j, ops))
					return (0);
				break ;
			}
		if (!label_line && !get_op(a->lines[i], ops))
			return (0);
	}
	return (match_labels(*l, *ops));
}
