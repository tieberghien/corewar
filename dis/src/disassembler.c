/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disassembler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etieberg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 13:54:05 by etieberg          #+#    #+#             */
/*   Updated: 2018/04/24 14:40:47 by etieberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm.h"

t_op    g_op_tab[16] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0, 1},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0, 1},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0, 1},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0, 1},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0, 1},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0, 1},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0, 1},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1, 0},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1, 0},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0, 1},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1, 0},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0, 1},
};

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

static int		get_opsize(char *op_size)
{
	size_t i;

	i = 0;
	while (i < ft_strlen(op_size))
	{
		ft_printf("%c\n", op_size[i]);
		i++;
	}
	return (0);
}

static int		get_opname(char *op)
{
	int	i;

	i = -1;
	while (++i < 16)
	{
		if (ft_atoi(op) ==  g_op_tab[i].op_code)
			ft_printf("%s\n", g_op_tab[i].name);
	}
	return (0);
}

int		disassembler(unsigned char *instr, size_t size)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!(str = (char *)malloc(sizeof(char) * size)))
		exit(0);
	while (i < size)
	{
		str = ft_itoabase(instr[i], 10, str);
		get_opname(str);
		if (++i < size)
		{
			str = ft_itoabase(instr[i], 2, str);
			ft_printf("%s\n", str);
			get_opsize(str);
			str = ft_itoabase(instr[i], 10, str);
			ft_printf("%s\n", str);
		//	get_opsize(str);
		}
		i += ft_atoi(str);
	//	ft_printf("%s\n", str);
	}
	free(str);
	return (0);
}
