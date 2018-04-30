/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_whitespace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 19:38:54 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/04/30 15:48:22 by etieberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_rm_lead_space(char *line)
{
	int		i;
	int		j;
	char	*dst;

	j = 0;
	i = 0;
	if (line == NULL)
		return (NULL);
	while ((line[i] == ' ' || line[i] == '\t') && line[i])
		i++;
	if (!(dst = malloc((ft_strlen(line) - i + 1))))
		return (NULL);
	while (line[i])
		dst[j++] = line[i++];
	dst[j] = '\0';
	free(line);
	return (dst);
}
