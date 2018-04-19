/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 12:40:17 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/04/19 15:20:17 by etieberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	is_comment(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (*line == '#' || !*line)
		return (1);
	if (*line == ';' || !*line)
		return (1);
	return (0);
}

static int	check_at_top(t_am *a)
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

static char	*rm_trailing_comment(char *line)
{
	int		i;
	char	*dst;
	int		j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '#')
			break ;
		else if (line[i] == ';')
			break ;
		i++;
	}
	if (!(dst = malloc(i + 1)))
		return (NULL);
	while (j < i)
	{
		dst[j] = line[j];
		j++;
	}
	dst[j] = '\0';
	free(line);
	return (dst);
}

static void	clean_lines(t_am *a)
{
	int	i;

	i = 0;
	while (i < a->lc)
	{
		a->lines[i] = ft_rm_lead_space(a->lines[i]);
		if (ft_strchr(a->lines[i], '#'))
			a->lines[i] = rm_trailing_comment(a->lines[i]);
		else if (ft_strchr(a->lines[i], ';'))
			a->lines[i] = rm_trailing_comment(a->lines[i]);
		i++;
	}
}

int			read_file(int fd, t_am *a)
{
	int		j;
	int		quote;
	char	*line;

	quote = 0;
	a->lc = 0;
	a->eoc = 0;
	while (get_next_line(fd, &line) > 0)
	{
		j = 0;
		while (line[j])
			if (line[j++] == '"')
				quote++;
		if (!is_comment(line) || quote % 2)
		{
			a->lines = ft_add_charpointer(a->lines, line, a->lc);
			a->lc++;
		}
		else
			free(line);
	}
	if (!get_name(a) || !get_comment(a) || !check_at_top(a))
		return (0);
	clean_lines(a);
	return (1);
}
