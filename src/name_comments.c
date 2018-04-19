/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_comments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 18:54:22 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/04/19 15:43:42 by etieberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	get_first_quote(char *line)
{
	int	j;

	j = 0;
	while (line[j])
	{
		if (line[j] == '"' && line[j + 1] != '\n')
			return (j + 1);
		j++;
	}
	return (-1);
}

static int	get_second_quote(t_am *a, int i, int j, int *count)
{
	int	original_i;

	if (a->lines[i][j] == '"')
		return (j + 1);
	original_i = i;
	while (1)
	{
		if (!a->lines[i][j])
		{
			*count += 1;
			i++;
			j = -1;
		}
		else if (a->lines[i][j] == '"')
			break ;
		j++;
		if (*count == a->lc - original_i)
			return (-1);
	}
	return (j);
}

static char	*read_name_comm(t_am *a, int i)
{
	int		j;
	int		k;
	char	*name;
	int		count;

	count = 0;
	if ((k = get_first_quote(a->lines[i])) == -1)
		return (NULL);
	if ((j = get_second_quote(a, i, k, &count)) == -1)
		return (NULL);
	name = malloc(1);
	name[0] = '\0';
	while (count-- > 0)
	{
		name = ft_strjoin_freeboth(name, ft_strsub(a->lines[i], k,
		ft_strlen(a->lines[i]) - k));
		name = ft_strjoin_free(name, "\n");
		i++;
		k = 0;
	}
	a->eoc = (i > a->eoc) ? i : a->eoc;
	return (ft_strjoin_freeboth(name, ft_strsub(a->lines[i],
	k, j - k)));
}

int			get_name(t_am *a)
{
	int	i;
	int	j;
	int	name_i;
	int	count;

	count = 0;
	i = 0;
	while (i < a->lc)
	{
		j = 0;
		while (a->lines[i][j] == '\t' || a->lines[i][j] == ' ')
			j++;
		if (!STRCMP_NAME)
		{
			count++;
			name_i = i;
		}
		i++;
	}
	if (count != 1 || !(a->name = read_name_comm(a, name_i)))
		return (0);
	if (a->name[0] == '"')
		a->name[0] = '\0';
	if (ft_strlen(a->name) > PROG_NAME_LENGTH)
		return_failure(NAME_LONG, NULL);
	return (1);
}

int			get_comment(t_am *a)
{
	int	i;
	int	j;
	int	comment_i;
	int	count;

	i = 0;
	count = 0;
	while (i < a->lc)
	{
		j = 0;
		while (a->lines[i][j] == '\t' || a->lines[i][j] == ' ')
			j++;
		if (!STRCMP_CMNT)
		{
			count++;
			comment_i = i;
		}
		i++;
	}
	if (count != 1 || !(a->comment = read_name_comm(a, comment_i)))
		return (0);
	if (a->comment[0] == '"')
		a->comment[0] = '\0';
	if (ft_strlen(a->name) > COMMENT_LENGTH)
		return_failure(COMMENT_LONG, NULL);
	return (1);
}
