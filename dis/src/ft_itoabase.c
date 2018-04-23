/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoabase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etieberg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 16:59:37 by etieberg          #+#    #+#             */
/*   Updated: 2018/04/23 17:04:35 by etieberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm.h"

static int	ft_intlen(intmax_t n, int base)
{
	int		size;

	size = 1;
	if (n < 0 && base == 10)
		size++;
	while (n >= base || n <= -base)
	{
		size++;
		n /= base;
	}
	return (size);
}

char		*ft_itoabase(intmax_t n, int base, char *s)
{
	int		i;
	int		size;
	char	itoa_base[16];

	if (base < 2 || base > 16)
		return (NULL);
	i = 0;
	ft_strncpy(itoa_base, "0123456789abcdef", base);
	size = ft_intlen(n, base);
	if (n < 0 && base == 10)
		s[i++] = '-';
	s[size] = '\0';
	while (size - 1 >= i)
	{
		s[size - 1] = itoa_base[ft_abs(n % base)];
		size--;
		n /= base;
	}
	return (s);
}
