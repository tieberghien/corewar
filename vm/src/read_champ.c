/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syboeuf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 16:25:48 by syboeuf           #+#    #+#             */
/*   Updated: 2018/05/10 17:29:06 by syboeuf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		cpyinst(unsigned char **str, int buffsize, unsigned char *buf, int fd)
{
	int i;

	i = read(fd, buf, buffsize);
	if (i != buffsize)
		return (-1);
	if (!(*str = (unsigned char*)malloc(sizeof(unsigned char) * buffsize)))
		return (-1);
	*str = ft_memcpy((char*)*str, (char*)buf, buffsize);
	return (i);
}

int		readstr(char **str, int buffsize, unsigned char *buf, int fd)
{
	int i;

	i = read(fd, buf, buffsize);
	if (!(*str = (char*)malloc(sizeof(char) * buffsize + 1)))
		return (-1);
	(*str)[buffsize] = '\0';
	*str = ft_strncpy(*str, (char*)buf, buffsize);
	return (i);
}

int		read_file(t_champs *champs)
{
	int				i;
	int				j;
	unsigned char	buf[COMMENT_LENGTH];

	i = read(champs->fd, buf, 4);
	if (ft_memcmp((void *)buf, g_magic, 4))
		return (ft_printf("You're not a real.cor...\n"));
	j = i;
	if ((i = readstr(&champs->name, PROG_NAME_LENGTH, buf, champs->fd)) < 0)
		ft_printf("malloc error");
	j += i;
	lseek(champs->fd, 4, SEEK_CUR);
	i = read(champs->fd, buf, 4);
	if ((champs->size = buf[2] * 256 + buf[3]) == 0)
		return (ft_printf("champion empty"));
	if (buf[0] != 0 || buf[1] != 0 || champs->size > CHAMP_MAX_SIZE)
		return (ft_printf("%s is too big", champs->name));
	if ((i = readstr(&champs->comment, COMMENT_LENGTH, buf, champs->fd)) < 0)
		ft_printf("malloc error");
	j += i;
	lseek(champs->fd, 4, SEEK_CUR);
	if ((i = cpyinst(&champs->instructions, champs->size, buf, champs->fd)) < 0)
		ft_printf("malloc error");
	j += i;
	return (0);
}

int		oc_file(t_champs *champs, t_opts *opts)
{
	unsigned int i;

	i = -1;
	while (++i < opts->n_players)
	{
		champs[i].fd = open(champs[i].file_name, O_RDONLY);
		if (champs[i].fd == -1 || lseek(champs[i].fd, 4, SEEK_SET) == -1)
			return (ft_printf("champion %s is a lie!\n", champs[i].file_name));
		if (lseek(champs[i].fd, PROG_NAME_LENGTH, SEEK_CUR) == -1)
			return (ft_printf("champion %s is a lie!\n", champs[i].file_name));
		if (lseek(champs[i].fd, 4, SEEK_SET) == -1)
			return (ft_printf("champion %s is a lie!\n", champs[i].file_name));
		if (lseek(champs[i].fd, 4, SEEK_CUR) == -1)
			return (ft_printf("champion %s is a lie!\n", champs[i].file_name));
		if (lseek(champs[i].fd, COMMENT_LENGTH, SEEK_CUR) == -1)
			return (ft_printf("champion %s is a lie!\n", champs[i].file_name));
		if (lseek(champs[i].fd, 4, SEEK_SET) == -1)
			return (ft_printf("champion %s is a lie!\n", champs[i].file_name));
		lseek(champs[i].fd, 0, SEEK_SET);
		if (read_file(champs + i) > 0)
			return (1);
		close(champs[i].fd);
	}
	return (display_intro(champs, *opts));
}
