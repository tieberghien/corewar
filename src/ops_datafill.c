/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_formatcheck.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 16:33:16 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/03/12 18:40:09 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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

int	fill_reg(char *line, t_ops *ops, int pc)
{
	int		i;
	long	n;

	i = 1;
	if (line[0] != 'r')
		return (0);
	if (!ft_isdigit(line[1]))
		return (0);
	n = ft_atol(line + 1);
	if (n > REG_NUMBER || n < 0)
		return (0);
	while (ft_isdigit(line[i]))
		i++;
	while (line[i] != ',' && line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	write_to_data(ops->data, (int)n, pc, 1);
	ops->cb[ops->cb_i++] = 1;
	return (1);
}

static	int	percent_case(char *line, t_ops *ops, int size, int pc)
{
	int	i;

	i = 0;
	if (!line[i])
		return (0);
	while (line[i] != ' ' && line[i] != '\t' && line[i] && line[i] != ',')
		i++;
	ops->labels = ft_add_charpointer(ops->labels, ft_strndup(line, i), ops->lc);
	ops->put[ops->lc++] = pc;
	ops->cb[ops->cb_i++] = 2;
	return (size);
}

int	fill_index(char *line, t_ops *ops, int pc, int size)
{
	int		i;
	long	n;

	i = 0;
	if (!line[i] || line[i++] != '%')
		return (0);
	if (!line[i] || (!ft_isdigit(line[i]) && line[i] != ':' && line[i] != '-'))
		return (0);
	if (line[i] == ':')
		return (percent_case(line + ++i, ops, size, pc));
	n = ft_atol(line + i);
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
	write_to_data(ops->data, (int)n, pc, size);
	ops->cb[ops->cb_i++] = 2;
	return (size);
}

int	fill_value(char *line, t_ops *ops, int pc)
{
	int		i;
	long	n;

	i = 0;
	if (line[i] == ':')
		return (percent_case(line + 1, ops, 2, pc));
	if (!line[i] || (!ft_isdigit(line[i]) && line[i] != '-'))
		return (0);
	n = ft_atol(line + i);
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
	write_to_data(ops->data, (int)n, pc, 2);
	ops->cb[ops->cb_i++] = 3;
	return (2);
}
