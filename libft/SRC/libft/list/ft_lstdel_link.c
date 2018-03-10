/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_link.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoncalv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 22:08:31 by jgoncalv          #+#    #+#             */
/*   Updated: 2018/03/02 15:33:36 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel_link(t_list **alst, t_list *link,
void (*del)(void *, size_t))
{
	t_list	*tmp;

	if (*alst && link)
	{
		if (*alst == link)
		{
			if ((*alst)->next)
				*alst = (*alst)->next;
			else
				*alst = NULL;
		}
		else
		{
			tmp = *alst;
			while (tmp && tmp->next != link)
				tmp = tmp->next;
			tmp->next = link->next;
		}
		del(link->content, link->content_size);
		free(link);
		link = NULL;
	}
}
