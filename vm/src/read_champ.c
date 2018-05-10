/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etieberg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 17:23:28 by etieberg          #+#    #+#             */
/*   Updated: 2018/05/10 18:08:16 by etieberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	return_failure(char *str, char *op)
{
	ft_putstr_fd(str, 2);
	if (op != NULL)
		ft_putendl_fd(op, 2);
	else
		ft_putchar_fd('\n', 2);
	exit(0);
}

int		cpyinst(unsigned char **str, int buffsize, unsigned char *buf, int fd)
{
	int i;

	if ((i = read(fd, buf, buffsize)) != buffsize)
		return (-1);
	buf[buffsize] = '\0';
	if (!(*str = malloc(buffsize + 1)))
		return (-1);
	ft_memcpy((char *)*str, (char *)buf, buffsize + 1);
	return (i);
}

int		readstr(char **str, int buffsize, unsigned char *buf, int fd)
{
	int		i;
	char	*tmp;
	int		len;

	i = read(fd, buf, buffsize);
	len = ft_strlen((char *)buf);
	if (i != buffsize)
		return (-1);
	buf[len] = '\0';
	tmp = ft_strdup((char *)buf);
	*str = tmp;
	return (i);
}

int		read_file(t_champs *champs)
{
	int				i;
	int				j;
	unsigned char	buf[COMMENT_LENGTH];

	j = 0;
	i = read(champs->fd, buf, 4);
	if (ft_memcmp((void *)buf, g_magic, 4))
		return_failure(MAGIC, NULL);
	j += i;
	if ((i = readstr(&champs->name, PROG_NAME_LENGTH, buf, champs->fd)) < 0)
		return_failure(NAME, NULL);
	j += i;
	lseek(champs->fd, 4, SEEK_CUR);
	i = read(champs->fd, buf, 4);
	if ((champs->size = buf[2] * 256 + buf[3]) == 0)
		return_failure(EMPTY, NULL);
	if (buf[0] != 0 || buf[1] != 0 || champs->size > CHAMP_MAX_SIZE)
		return_failure(BIG, NULL);
	if ((i = readstr(&champs->comment, COMMENT_LENGTH, buf, champs->fd)) < 0)
		return_failure(COMMENT, NULL);
	j += i;
	lseek(champs->fd, 4, SEEK_CUR);
	if ((i = cpyinst(&champs->instructions, champs->size, buf, champs->fd)) < 0)
		return_failure(INSTR, NULL);
	return (0);
}

int		oc_file(t_champs *champs, t_opts *opts)
{
	unsigned int i;

	i = -1;
	while (++i < opts->n_players)
	{
		champs[i].fd = open(champs[i].file_name, O_RDONLY);
		if (champs[i].fd == -1)
			return_failure("File not open", NULL);
		if (lseek(champs[i].fd, 4, SEEK_SET) == -1)
			return_failure("Your champion is a lie!", NULL);
		if (lseek(champs[i].fd, PROG_NAME_LENGTH, SEEK_CUR) == -1)
			return_failure("Your champion is a lie!", NULL);
		if (lseek(champs[i].fd, 4, SEEK_SET) == -1)
			return_failure("Your champion is a lie!", NULL);
		if (lseek(champs[i].fd, 4, SEEK_CUR) == -1)
			return_failure("Your champion is a lie!", NULL);
		if (lseek(champs[i].fd, COMMENT_LENGTH, SEEK_CUR) == -1)
			return_failure("Your champion is a lie!", NULL);
		if (lseek(champs[i].fd, 4, SEEK_SET) == -1)
			return_failure("Your champion is a lie!", NULL);
		lseek(champs[i].fd, 0, SEEK_SET);
		read_file(champs + i);
		close(champs[i].fd);
	}
	return (display_intro(champs, *opts));
}
