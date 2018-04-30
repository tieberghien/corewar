/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_bytes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaudry <agaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 17:09:43 by agaudry           #+#    #+#             */
/*   Updated: 2017/07/13 17:09:43 by agaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

/*
** Fonctions de swap des octets pour passer en big endian (versions sur 4 et
** sur 2 octets)
*/

int			ft_swap_bytes(int i)
{
	int	res;

	res = ((i & 0x000000FF) << 24
		| (i & 0x0000FF00) << 8
		| (i & 0x00FF0000) >> 8
		| (i & 0xFF000000) >> 24);
	return (res);
}

short int	ft_swap_bytes_short(int i)
{
	short int	res;

	res = ((i & 0x000000FF) << 8
		| (i & 0x0000FF00) >> 8);
	return (res);
}
