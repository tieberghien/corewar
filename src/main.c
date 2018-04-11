/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 18:34:20 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/04/11 17:18:10 by etieberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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

int 		main(int ac, char **av)
{
	int		fd;
	t_am	a;

	if (ac < 2)
		return (0);
	fd = open(av[ac - 1], O_RDONLY);
	if (fd == -1)
		return (0);
	if (!read_file(fd, &a))
		return (0);
   	if (!assembler(&a, av[1], fd))
	{
		ft_putstr("ERRORRRRRRR!!!!!!!! AAAHHHHHHHGGGHH\n");
		return (0);
	}
}
