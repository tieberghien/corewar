/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_formatcheck.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 16:33:16 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/03/13 12:29:07 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	check_characters(char *line, long n)
{
	int	i;

	i = 0;
	if (n > INT_MAX || n < INT_MIN)
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

static	void	colon_case(char *line, t_ops *ops, int count, int *cb)
{
	int	i;

	i = 0;
	if (!line[i])
		return ;
	while (line[i] != ' ' && line[i] != '\t' && line[i] && line[i] != ',')
		i++;
	ops->labels = ft_add_charpointer(ops->labels, ft_strndup(line, i), ops->lc);
	ops->put[ops->lc++] = ops->pc;
	*cb |=  2 << ((3 - count) * 2);
}

int	go_next_param(char *line)
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

void	fill_reg(char *line, t_ops *ops, int count, int *cb)
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

void	fill_index(char *line, t_ops *ops, int count, int *cb)
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
		colon_case(line + ++i, ops, count, cb);
		ops->pc += ops->small;
		return ;
	}
	n = ft_atol(line + i);
	if (!check_characters(line + i, n))
		return ;
	write_to_data(ops->data, (int)n, ops->pc, ops->small);
	*cb |= 2 << ((3 - count) * 2);
	ops->pc += ops->small;
}

void	fill_value(char *line, t_ops *ops, int count, int *cb)
{
	int		i;
	long	n;

	i = 0;
	if (line[i] == ':')
	{
		colon_case(line + 1, ops, count, cb);
		ops->pc += 2;
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
