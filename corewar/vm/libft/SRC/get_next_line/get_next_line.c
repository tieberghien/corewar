/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoncalv <jgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 17:22:44 by jgoncalv          #+#    #+#             */
/*   Updated: 2018/03/02 15:19:14 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void		del(t_gnl *s_gnl, size_t size)
{
	(void)size;
	if (s_gnl->str)
		ft_strdel(&s_gnl->str);
	ft_memdel((void**)&s_gnl);
}

static int		read_fd(t_gnl *s_gnl)
{
	char	buf[BUFF_SIZE + 1];
	char	*tmp;
	int		ret;

	ret = 0;
	if (s_gnl->str)
	{
		while (!ft_strchr(s_gnl->str, '\n') &&
				(ret = read(s_gnl->fd, buf, BUFF_SIZE)) > 0)
		{
			buf[ret] = '\0';
			tmp = ft_strjoin(s_gnl->str, buf);
			ft_strdel(&s_gnl->str);
			s_gnl->str = tmp;
		}
		if (ret == 0 && s_gnl->str[0] != '\0')
			return (1);
	}
	return (ret);
}

static int		fill_str(char **line, t_gnl *s_gnl)
{
	char	*tmp;
	int		ret;
	int		len;

	ret = read_fd(s_gnl);
	if (s_gnl->str && s_gnl->str[0] != '\0' && ret > 0)
	{
		if ((tmp = ft_strchr(s_gnl->str, '\n')))
		{
			len = ft_strlen(s_gnl->str) - ft_strlen(tmp);
			*line = ft_strsub(s_gnl->str, 0, len);
			tmp = ft_strdup(s_gnl->str + len + 1);
			ft_strdel(&s_gnl->str);
			s_gnl->str = tmp;
		}
		else
		{
			*line = ft_strdup(s_gnl->str);
			ft_strdel(&s_gnl->str);
		}
		return (1);
	}
	if (s_gnl->str)
		ft_strdel(&s_gnl->str);
	return (ret);
}

static t_list	*check_fd(t_list *l_gnl, int fd)
{
	while (l_gnl)
	{
		if (((t_gnl*)l_gnl->content)->fd == fd)
			return (l_gnl);
		l_gnl = l_gnl->next;
	}
	return (NULL);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*l_gnl;
	t_list			*maillon;
	t_gnl			*s_gnl;
	t_gnl			new_gnl;
	int				ret;

	ret = 0;
	if (fd < 0 || !line)
		return (-1);
	if (!(maillon = check_fd(l_gnl, fd)))
	{
		new_gnl.str = ft_strnew(0);
		new_gnl.fd = fd;
		if (new_gnl.str && (ret = fill_str(line, &new_gnl)) > 0)
			ft_lstadd(&l_gnl, ft_lstnew(&new_gnl, sizeof(new_gnl)));
	}
	else
	{
		s_gnl = maillon->content;
		if ((ret = fill_str(line, s_gnl)) <= 0)
			ft_lstdel_link(&l_gnl, maillon, (void*)del);
	}
	return (ret);
}
