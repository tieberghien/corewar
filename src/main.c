/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 18:34:20 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/03/12 17:35:34 by slynn-ev         ###   ########.fr       */
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

int		create_cor(char *pname, int fd)
{
	int	len;
	int	i;

	len = ft_strlen(pname);
	i = len;
	while (--i)
		if (pname[i] == '.')
			break ;
	pname = ft_strndup(pname, i);
	pname = ft_strjoin_free(pname, ".cor");
	if (close(fd) || (fd = open(pname, O_CREAT | O_WRONLY, 0666)) < 1)
		return (0);
	return (fd);
}

void	put_int(unsigned int num, int fd)
{
	unsigned char	mn[4];
	
	mn[0] = (num >> 24) & 255;
	mn[1] = (num >> 16) & 255;
	mn[2] = (num >> 8) & 255;
	mn[3] = num & 255;
	write(fd, mn, 4);
}

int		print_namecomm(t_am *a, int fd, int prog_size)
{
	int				len;
	int				zero;

	zero = 0;
	put_int(COREWAR_EXEC_MAGIC, fd);
	len = ft_strlen(a->name);
	write(fd, a->name, len);
	while (len++ < PROG_NAME_LENGTH + 4)
		write(fd, &zero, 1);
	len = ft_strlen(a->comment);
	put_int(prog_size, fd);
	write(fd, a->comment, len);
	while (len++ < COMMENT_LENGTH + 4)
		write(fd, &zero, 1);
	return (1);
}

int		find_labels(t_label *l, t_ops *ops)
{
	int		i;
	t_label *tmp;
	
	while (ops)
	{
		i = -1;
		while (++i < ops->lc)
		{
			tmp = l;
			while (tmp)
			{
				if (!ft_strcmp(tmp->name, ops->labels[i]))
				{
					write_to_data(ops->data, tmp->address - ops->addr,
					ops->put[i], ops->small);
					break ;
				}
				tmp = tmp->nxt;
			}
			if (!tmp)
				return (0);
		}
		ops = ops->nxt;
	}
	return (1);
}

void	print_ops(t_ops *ops, int fd)
{
	t_ops *tmp;

	while (ops)
	{
		write(fd, ops->data, ops->pc);
		tmp = ops;
		ops = ops->nxt;
		free(tmp);
	}
}

int		assembler(t_am *a, char *prog_name, int fd)
{
	t_label	*l;
	t_ops	*ops;
	
	l = NULL;
	ops = NULL;
	a->eoc = 0;
	if (!get_name(a) || !get_comment(a) || !check_at_top(a))
		return (0);
	remove_leading_whitespaces(a);
	build_operations(a, &l, &ops);
	find_labels(l, ops);
	fd = create_cor(prog_name, fd);
	print_namecomm(a, fd, get_address(ops));
	print_ops(ops, fd);
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
	//do last prog in list, not av[1]
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
	if (!assembler(&a, av[1], fd))
	{
		ft_putstr("ERRORRRRRRR!!!!!!!! AAAHHHHHHHGGGHH\n");
		return (0);
	}
}
