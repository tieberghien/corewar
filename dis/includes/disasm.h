/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disasm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etieberg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 13:14:21 by etieberg          #+#    #+#             */
/*   Updated: 2018/04/23 15:05:40 by etieberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISASM_H
# define DISASM_H

# include <limits.h>
# include "op.h"
# include "libft.h"
# include <fcntl.h>

static unsigned char g_magic[] = {0, 234, 131, 243};

typedef struct		s_champ
{
	int				player_id;
	unsigned int	size;
	char			*name;
	char			*comment;
	char			*file_name;
	int				fd;
	unsigned char	*instructions;
}					t_champs;

int			oc_file(t_champs *champs);

#endif
