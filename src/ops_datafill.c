/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_formatcheck.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 16:33:16 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/04/30 15:51:23 by etieberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	check_characters(char *line, long n)
{
	int	i;

	i = 0;
	if (n > LONG_MAX || n < LONG_MIN)
		return (0);
	if (line[i] == '-')
		i++;
	while (ft_isdigit(line[i]))
		i++;
	while (line[i] != ',' && line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

static int	colon_case(char *line, t_ops *ops, int size)
{
	int	i;

	i = 0;
	if (!line[i])
		return (0);
	while (line[i] != ' ' && line[i] != '\t' && line[i] && line[i] != ',')
		i++;
	ops->labels = ft_add_charpointer(ops->labels, ft_strndup(line, i), ops->lc);
	ops->put[ops->lc][0] = ops->pc;
	ops->put[ops->lc++][1] = size;
	return (1);
}

void		fill_reg(char *line, t_ops *ops, int count, int *cb)
{
	int		i;
	long	n;

	i = 1;
	if (line[0] != 'r')
		return ;
	if (!ft_isdigit(line[1]))
		return ;
	n = ft_atol(line + 1);
	if (n > REG_NUMBER || n < 0)
		return ;
	if (!check_characters(line + i, n))
		return ;
	write_to_data(ops->data, (int)n, ops->pc, 1);
	*cb |= 1 << ((3 - count) * 2);
	ops->pc++;
}

void		fill_index(char *line, t_ops *ops, int count, int *cb)
{
	int		i;
	long	n;

	i = 0;
	if (!line[i] || line[i++] != '%')
		return ;
	if (!line[i] || (!ft_isdigit(line[i]) && line[i] != ':' && line[i] != '-'))
		return ;
	if (line[i] == ':')
	{
		if (!(colon_case(line + ++i, ops, ops->small)))
			return ;
		ops->pc += ops->small;
		*cb |= 2 << ((3 - count) * 2);
		return ;
	}
	n = ft_atol(line + i);
	if (!check_characters(line + i, n))
		return ;
	write_to_data(ops->data, (int)n, ops->pc, ops->small);
	*cb |= 2 << ((3 - count) * 2);
	ops->pc += ops->small;
}

void		fill_value(char *line, t_ops *ops, int count, int *cb)
{
	int		i;
	long	n;

	i = 0;
	if (line[i] == ':')
	{
		if (!(colon_case(line + 1, ops, 2)))
			return ;
		ops->pc += 2;
		*cb |= 3 << ((3 - count) * 2);
		return ;
	}
	if (!line[i] || (!ft_isdigit(line[i]) && line[i] != '-'))
		return ;
	n = ft_atol(line + i);
	if (!check_characters(line + i, n))
		return ;
	write_to_data(ops->data, (int)n, ops->pc, 2);
	*cb |= 3 << ((3 - count) * 2);
	ops->pc += 2;
}
