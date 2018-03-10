/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 19:44:10 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/03/10 20:04:49 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	add_os(t_opset **os, t_am *a, int i, int end)
{
	t_opset *tmp;

	if (*os == NULL)
	{
		if (!(*os = malloc(sizeof(t_opset)))
			return (NULL);
		os->name = ft_strsub(a->lines[i], 0, end);
	}	



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
		while (lines[i][j] != ' ' && lines[i][j])
			if (lines[i][j++] = ':')
				add_os(&os, a, i, j -2);
		i++;
	}
}
