/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 19:44:10 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/03/10 20:24:26 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	add_os(t_opset **os, t_am *a, int i, int end)
{
	t_opset	*tmp;
	t_opset	*new;

	if (*os == NULL)
	{
		if (!(*os = malloc(sizeof(t_opset))))
			return ;
		(*os)->name = ft_strsub(a->lines[i], 0, end);
		(*os)->nxt = NULL;
		return ;
	}
	tmp = *os;
	while (tmp->nxt != NULL)
		tmp = tmp->nxt;
	if (!(new = malloc(sizeof(t_opset))))
		return ;
	new->name = ft_strsub(a->lines[i], 0, end);
	new->nxt = NULL;
	tmp->nxt = new;
}

int		build_operations(t_am *a)
{
	int		i;
	int		j;
	t_opset *os;

	i = a->eoc;
	os = NULL;
	while (i < a->lc)
	{
		j = 0;
		while (a->lines[i][j] != ' ' && a->lines[i][j] != '\t' && a->lines[i][j])
			if (a->lines[i][j++] == ':')
			{
				add_os(&os, a, i, j - 1);
				break ;
			}
		i++;
	}
	while (os != NULL)
	{
		ft_printf("%s\n", os->name);
		os = os->nxt;
	}
	return (1);
}
