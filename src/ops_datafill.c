/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_formatcheck.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 16:33:16 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/03/11 23:08:31 by slynn-ev         ###   ########.fr       */
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

int	fill_reg(char *line, char *data, int index)
{
	int		i;
	long	n;

	i = 1;
	if (data)
		;
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
		if (line[i] != ' ' && line[i++] != '\t')
			return (0);
//	data = fill_data(data, (int)n, 1);
	return (1);
}

int	percent_case(char *line, t_ops *ops)
{
	int	i;

	i = 0;
	while (line[i] != ' ' && line[i] != '\t' && line[i] && line[i] != ',')
		i++;
	ops->labels = ft_add_charpointer(ops->labels, ft_strndup(line, i), ops->lc);
	ops->lc++;
	return (size);
}

int	fill_index(char *line, t_ops *ops, int *pc, int size)
{
	int		i;
	long	n;

	i = 0;
	if (line[i++] != '%')
		return (0);
	if (!ft_isdigit(line[i]) && line[i] != ':' && line[i] != '-')
		return (0);
	if (line[i] == ':')
		return (percent_case(line + ++i, ops));
	n = ft_atol(line + i);
	if (n > INT_MAX || n < INT_MIN)
		return (0);
	while (ft_isdigit(line[i]))
		i++;
	while (line[i] != ',' && line[i])
		if (line[i] != ' ' && line[i++] != '\t')
			return (0);
	//fill_data(data, (int)n, 1);
	return (size);
}

int	fill_value(char *line, t_ops *ops, int *pc, int size)
{
	int		i;
	long	n;

	i = 0;
	if (!ft_isdigit(line[i]) && line[i] != '-')
		return (0);
	n = ft_atol(line + i);
	if (n > INT_MAX || n < INT_MIN)
		return (0);
	while (ft_isdigit(line[i]))
		i++;
	while (line[i] != ',' && line[i])
		if (line[i] != ' ' && line[i++] != '\t')
			return (0);
	//fill_data(data, (int)n, 1);
	return (2);
}
