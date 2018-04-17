/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dis_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etieberg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 17:53:59 by etieberg          #+#    #+#             */
/*   Updated: 2018/04/17 16:48:27 by etieberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm.h"

int		main(int ac, char **av)
{
//	int		fd;
	t_champs champ;
//	t_am	a;

	if (ac < 2)
		return (0);
	/*
	fd = open(av[ac - 1], O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Can't read source file ", 2);
		ft_putstr_fd(av[1], 2);
		ft_putchar_fd('\n', 2);
		return (0);
	}
	if (!read_file(fd, &a))
	{
		ft_putstr_fd("SYNTAX ERROR\n", 2);
		exit(0);
	}
	if (!assembler(&a, av[1], fd))
	{
		ft_putstr("ERRORRRRRRR!!!!!!!! AAAHHHHHHHGGGHH\n");
		exit(0);
	}
	*/
	if (!(champ.file = (char *)malloc(sizeof(char) * sizeof(av[1]))))
		return (0);
	champ.file = ft_strcpy(champ.file, av[1]);
	oc_file(&champ);
	//disassembler
	return (0);
}
