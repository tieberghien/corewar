/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 11:17:30 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/04/30 15:49:16 by etieberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_freeboth(char const *s1, char const *s2)
{
	int		len;
	char	*dst;
	int		i;
	int		j;

	i = 0;
	if (s2 == NULL || s1 == NULL)
		return (NULL);
	if (!(len = ft_strlen((char *)s1) + ft_strlen((char *)s2)))
		return (NULL);
	if ((dst = (char *)malloc(sizeof(char) * (len + 1))))
	{
		j = 0;
		while (s1[j])
			dst[i++] = s1[j++];
		j = 0;
		while (s2[j])
			dst[i++] = s2[j++];
		dst[i] = '\0';
		free((void *)s1);
		free((void *)s2);
		return (dst);
	}
	return (NULL);
}
