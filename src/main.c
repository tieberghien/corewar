/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 18:34:20 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/04/13 12:59:49 by syboeuf          ###   ########.fr       */
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

char	*tmp(char *s)
{
	char *tmp;
	int i;
	int k;
	int a;

	if (!(tmp = (char*)malloc(sizeof(char) * ft_strlen(s) + 200)))
		return (NULL);
	i = 0;
	k = 0;
	a = 0;
	while (s[i])
	{
		if (a == 0 && s[i] == '%' && (s[i - 1] != ' ' || s[i - 1] != '\t'))
		{
			tmp[k] = ' ';
			k++;
			a = 1;
		}
		else
		{
			tmp[k] = s[i];
			i++;
			k++;
		}
	}
	tmp[k] = '\0';
	return (tmp);
}

int 		main(int ac, char **av)
{
	int		fd;
	t_am	a;
	int		i;

	i = 0;
	if (ac < 2)
		return (0);
	fd = open(av[ac - 1], O_RDONLY);
	if (fd == -1)
		return (0);
	read_file(fd, &a);
	while (i < a.lc)
	{
		a.lines[i] = tmp(a.lines[i]);
		i++;
	}
   	if (!assembler(&a, av[1], fd))
	{
		ft_putstr("ERRORRRRRRR!!!!!!!! AAAHHHHHHHGGGHH\n");
		return (0);
	}
}
