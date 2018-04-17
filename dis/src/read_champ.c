/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etieberg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 13:29:18 by etieberg          #+#    #+#             */
/*   Updated: 2018/04/17 16:30:19 by etieberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm.h"

static int readstr(char **str, int buffsize, char *buf, int fd)
{
	int i;

	i = read(fd, buf, buffsize);
	if (!(*str = (char*)malloc(sizeof(char) * buffsize + 1)))
		return (-1);
	(*str)[buffsize] = '\0';
	*str = ft_strncpy(*str, buf, buffsize);
	return (i);
}

static int read_file(t_champs *champs)
{
	int i;
	int j;
	char buf[COMMENT_LENGTH];

	j = 0;
	i = read(champs->fd, buf, 4);
	if (ft_memcmp((void *)buf, g_magic, 4))
		return(ft_printf("did you try to trick me? you're not a real.cor...    %d\n", j));
	j += i;
	if((i = readstr(&champs->name, PROG_NAME_LENGTH, buf, champs->fd)) < 0)
		ft_printf("malloc error");
	j += i;
	i = read(champs->fd, buf, 4);
	if (buf[0] != 0 ||  buf[1] != 0 || buf[2] * 256 + buf[3] > CHAMP_MAX_SIZE)
		return (ft_printf("%s is too big", champs->name));
	if ((i = readstr(&champs->comment, COMMENT_LENGTH, buf, champs->fd)) < 0)
		ft_printf("malloc error");
	j += i;
	if (i)
		return (ft_printf("number of data read = %d\n", j));
	return (0);
}

int	oc_file(t_champs *champs)
{
	unsigned int i;

	i = 0;
	champs->fd = open(champs->file, O_RDONLY);
	if (champs->fd == -1)
		return (ft_printf("File not open"));
	if (lseek(champs->fd, 4, SEEK_SET) == -1)
		return(ft_printf("champion %s is a lie!", champs->file));
	if (lseek(champs->fd, PROG_NAME_LENGTH, SEEK_CUR) == -1)
		return(ft_printf("champion %s is a lie!", champs->file));
	if (lseek(champs->fd, 4, SEEK_CUR) == -1)
		return(ft_printf("champion %s is a lie!", champs->file));    
	if (lseek(champs->fd, COMMENT_LENGTH, SEEK_CUR) == -1)
		return(ft_printf("champion %s is a lie!", champs->file));
	lseek(champs->fd, 0, SEEK_SET);
	read_file(champs);
//	ft_printf("%s\n", champs->comment);
	close(champs->fd);
	i++;
	return (0);
}
