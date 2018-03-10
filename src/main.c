/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 18:34:20 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/03/10 19:43:47 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	is_comment(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (*line == '#' || !*line)
		return (1);
	return (0);
}

int	check_at_top(t_am *a)
{
	int	quote;
	int	i;
	int	j;

	i = 0;
	quote = 0;
	while (i < a->lc)
	{
		j = 0;
		while (a->lines[i][j] == '\t' || a->lines[i][j] == ' ')
			j++;
		if (!quote || quote == 2)
		{
			if (STRCMP_NAME && STRCMP_CMNT)
				return (0);
			if (quote == 2)
			return (1);
		}
		while (a->lines[i][j])
			if (a->lines[i][j++] == '"')
				quote++;
		i++;	
	}
	return (0);
}

int			check_all(t_am *a)
{
	a->eoc = 0;
	if (!get_name(a) || !get_comment(a) || !check_at_top(a))
		return (0);
	remove_leading_whitespaces(a);
	build_operations(a);
	int i = 0;
	while (i < a->lc)
		ft_printf("%s\n", a->lines[i++]);
	ft_printf("%s\n", a->name);
	ft_printf("%s\n", a->comment);
	ft_printf("%d\n", a->eoc);
	return (1);
}

int 		main(int ac, char **av)
{
	int		fd;
	char	*line;
	t_am	a;
	int		quote;
	int		j;

	quote = 0;
	a.lc = 0;
	if (ac != 2)
		return (0);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (0);
	while (get_next_line(fd, &line) > 0)
	{
		j = 0;
		while (line[j])
			if (line[j++] == '"')
				quote++;
		if (!is_comment(line) || quote % 2)
		{
			a.lines = ft_add_charpointer(a.lines, line, a.lc);
			a.lc++;
		}
		else
			free(line);
	}
	if (!check_all(&a))
	{
		ft_putstr("ERRORRRRRRR!!!!!!!! AAAHHHHHHHGGGHH\n");
		return (0);
	}
}
