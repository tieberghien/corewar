/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disassembler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etieberg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 13:54:05 by etieberg          #+#    #+#             */
/*   Updated: 2018/04/17 16:48:30 by etieberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm.h"

int		create_s(char *pname, int fd)
{
	int	len;
	int	i;

	len = ft_strlen(pname);
	i = len;
	while (--i)
		if (pname[i] == '.')
			break ;
	pname = ft_strndup(pname, i);
	pname = ft_strjoin_free(pname, ".s");
	if (close(fd) || (fd = open(pname, O_CREAT | O_WRONLY, 0666)) < 1)
		return (0);
	ft_printf("Writing output program to %s\n", pname);
	free(pname);
	return (fd);
}

/*
int		disassembler(t_champs champ)
{
	return (0);
}
*/
