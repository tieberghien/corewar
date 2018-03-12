/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 18:34:20 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/03/12 18:40:37 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# define STRCMP_NAME ft_strncmp(a->lines[i] + j, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING))
# define STRCMP_CMNT ft_strncmp(a->lines[i] + j, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING))

# include <limits.h>
# include "libft.h"
# include "op.h"
# include <fcntl.h>

typedef struct		s_ops
{
	char			*name;
	char			data[20];
	int				lc;
	char			**labels;
	int				put[3];
	int				addr;
	int				end_addr;
	int				small;
	int				pc;
	int				cb[3];
	int				cb_i;
	struct s_ops		*nxt;
}					t_ops;

typedef struct 		s_label
{
	char			*name;
	int				address;
	struct s_label	*nxt;
}					t_label;

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
	char	*name;
	int		argc;
	int		params[3];	
	int		op_code;
	int		dur;
	char	effect[100];
	int		carry;
	int		small;
	int		ocp;
}				t_op;

int				get_name(t_am *a);
int				get_comment(t_am *a);
void			remove_leading_whitespaces(t_am *a);
int				get_op(char *line, t_ops **ops);
int				fill_value(char *line, t_ops *ops, int pc);
int				fill_reg(char *line, t_ops *ops, int pc);
int				go_next_param(char *line);
int				fill_index(char *line, t_ops *ops, int pc, int size);
int				build_operations(t_am *a, t_label **l, t_ops **ops);
int 			get_address(t_ops *ops);
void			write_to_data(char *data, int num, int index, int size);

#endif
