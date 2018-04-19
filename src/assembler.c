/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 13:18:27 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/04/19 18:38:59 by etieberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		create_cor(char *pname, int fd)
{
	int	len;
	int	i;

	len = ft_strlen(pname);
	i = len;
	while (--i)
		if (pname[i] == '.')
			break ;
	if (*(pname + i + 1) != 's')
		return_failure(FILE_FORMAT, NULL);
	pname = ft_strndup(pname, i);
	pname = ft_strjoin_free(pname, ".cor");
	if (close(fd) || (fd = open(pname, O_CREAT | O_WRONLY, 0666)) < 1)
		return (0);
	ft_printf("Writing output program to %s\n", pname);
	free(pname);
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

void	print_namecomm(t_am *a, int fd, int prog_size)
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
}

void	print_free_ops(t_ops *ops, int fd)
{
	t_ops	*tmp;
	int		i;

	while (ops)
	{
		write(fd, ops->data, ops->pc);
		tmp = ops;
		free(tmp->name);
		i = 0;
		while (i < ops->lc)
		{
			free(ops->labels[i++]);
			if (i == ops->lc)
				free(ops->labels);
			i++;
		}
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
	if (!build_operations(a, &l, &ops))
	{
		ft_putstr("LEXICAL ERROR\n");
		exit(0);
	}
	fd = create_cor(prog_name, fd);
	print_namecomm(a, fd, get_address(ops));
	print_free_ops(ops, fd);
	free_all(a, l);
	return (1);
}
