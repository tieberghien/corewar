/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etieberg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 13:29:18 by etieberg          #+#    #+#             */
/*   Updated: 2018/04/24 13:38:47 by etieberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm.h"

static int cpyinst(unsigned char **str, int buffsize, unsigned char *buf, int fd)
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

static int readstr(char **str, int buffsize, unsigned char *buf, int fd)
{
	int i;

	i = read(fd, buf, buffsize);
	if (!(*str = (char*)malloc(sizeof(char) * buffsize + 1)))
		return (-1);
	(*str)[buffsize] = '\0';
	*str = ft_strncpy(*str, (char*)buf, buffsize);
	return (i);
}

static int read_file(t_champs *champs)
{
	int i;
	int j;
	unsigned char buf[COMMENT_LENGTH];

	j = 0;
	i = read(champs->fd, buf, 4);
	if (ft_memcmp((void *)buf, g_magic, 4))
		return(ft_printf("did you try to trick me? you're not a real.cor...    %d\n", j));
	j += i;
	if((i = readstr(&champs->name, PROG_NAME_LENGTH, buf, champs->fd)) < 0)
		ft_printf("malloc error");
	j += i;
	lseek(champs->fd, 4, SEEK_CUR);
	i = read(champs->fd, buf, 4);
	if ((champs->size = buf[2] * 256 + buf[3]) == 0)
		return (ft_printf("champion empty"));
	if (buf [0] != 0 || buf[1] != 0 || champs->size > CHAMP_MAX_SIZE)
		return (ft_printf("%s is too big", champs->name));
	if((i = readstr(&champs->comment, COMMENT_LENGTH, buf, champs->fd)) < 0)
		ft_printf("malloc error");
	j += i;
	lseek(champs->fd, 4, SEEK_CUR);
	if((i = cpyinst(&champs->instructions, champs->size, buf, champs->fd)) < 0)
		ft_printf("malloc error");
	j += i;
	return (0);
}

int	oc_file(t_champs *champs)
{
	champs->fd = open(champs->file_name, O_RDONLY);
	if (champs->fd == -1)
		return (ft_printf("File not open"));
	if (lseek(champs->fd, 4, SEEK_SET) == -1)
		return(ft_printf("champion %s is a lie!", champs->file_name));
	if (lseek(champs->fd, PROG_NAME_LENGTH, SEEK_CUR) == -1)
		return(ft_printf("champion %s is a lie!", champs->file_name));
	if (lseek(champs->fd, 4, SEEK_SET) == -1)
		return(ft_printf("champion %s is a lie!", champs->file_name));
	if (lseek(champs->fd, 4, SEEK_CUR) == -1)
		return(ft_printf("champion %s is a lie!", champs->file_name));    
	if (lseek(champs->fd, COMMENT_LENGTH, SEEK_CUR) == -1)
		return(ft_printf("champion %s is a lie!", champs->file_name));
	if (lseek(champs->fd, 4, SEEK_SET) == -1)
		return(ft_printf("champion %s is a lie!", champs->file_name));
	lseek(champs->fd, 0, SEEK_SET);
	if(read_file(champs) > 0)
		return (1);
	close(champs->fd);
	disassembler(champs->instructions, champs->size);
	/*
	size_t	i = 0;
	char *str = malloc(champs->size);
	char *bin = malloc(champs->size);
	while (i < champs->size)
	{
		ft_printf("HHX %hhx\n", champs->instructions[i]);
		str = ft_itoabase(champs->instructions[i], 16, str);
		ft_printf("STR %s\n", str);
		bin = ft_itoabase(champs->instructions[i], 2, str);
		ft_printf("BIN %s\n", bin);
		ft_printf("---------------------------------------\n");
		i++;
	}
	*/
	return (1);
}
