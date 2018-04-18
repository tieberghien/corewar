/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 18:34:20 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/04/18 16:16:58 by etieberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	return_invparams(int n, char *type, char *op)
{
	ft_putstr_fd("Invalid parameter ", 2);
	ft_putnbr_fd(n, 2);
	ft_putstr_fd(" type ", 2);
	ft_putstr_fd(type, 2);
	ft_putstr_fd(" for instruction ", 2);
	ft_putendl_fd(op, 2);
	exit(0);
}

void	return_failure(char *str, char *op)
{
	ft_putstr_fd(str, 2);
	if (op != NULL)
		ft_putendl_fd(op, 2);
	else
		ft_putchar_fd('\n', 2);
	exit(0);
}

void	write_to_data(char *data, int num, int index, int size)
{
	int	len;

	len = 8 * (size - 1);
	while (len >= 0)
	{
		data[index++] = (num >> len) & 255;
		len -= 8;
	}
}

void	free_all(t_am *a, t_label *l)
{
	t_label *tmp;
	int		i;

	i = 0;
	free(a->name);
	free(a->comment);
	while (i < a->lc)
		free(a->lines[i++]);
	free(a->lines);
	while (l)
	{
		free(l->name);
		tmp = l;
		l = l->nxt;
		free(tmp);
	}
}

int		main(int ac, char **av)
{
	int		fd;
	t_am	a;

	if (ac < 2)
		return (0);
	fd = open(av[ac - 1], O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Can't read source file ", 2);
		ft_putstr_fd(av[1], 2);
		ft_putchar_fd('\n', 2);
		return (0);
	}
	if (!read_file(fd, &a))
	{
		ft_putstr_fd("SYNTAX ERROR\n", 2);
		exit(0);
	}
	if (!assembler(&a, av[1], fd))
	{
		ft_putstr("ERRORRRRRRR!!!!!!!! AAAHHHHHHHGGGHH\n");
		exit(0);
	}
	close(fd);
	return (0);
}
