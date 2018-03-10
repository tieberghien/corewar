/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 18:34:20 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/03/10 19:41:09 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# define STRCMP_NAME ft_strncmp(a->lines[i] + j, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING))
# define STRCMP_CMNT ft_strncmp(a->lines[i] + j, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING))

# include <stdio.h>
# include "libft.h"
# include "op.h"
# include <fcntl.h>

typedef struct 		s_opset
{
	char			*name;
	int				oc;
	int				address;
//	t_op	*ops;
	struct opset	*nxt;
}				t_opset;

typedef struct	s_am
{
	char	**lines;
	int		lc;
	char	*name;
	char	*comment;
	int		eoc;
}				t_am;

typedef struct s_op
{
	char	cmnd[100];
	int		argc;
	int		params[3];	
	int		op_code;
	int		dur;
	char	effect[100];
	int		carry;
	int		unknown;
}				t_op;

int				get_name(t_am *a);
int				get_comment(t_am *a);
void			remove_leading_whitespaces(t_am *a);

#endif
