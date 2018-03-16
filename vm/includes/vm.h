/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etieberg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 17:44:43 by etieberg          #+#    #+#             */
/*   Updated: 2018/03/16 17:24:54 by etieberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <limits.h>
# include "libft.h"
# include <fcntl.h>

/* dump coded on 32o + id_player between [1-99] */

typedef struct	s_opts
{
	int			n_cycles;
	short		*id_player;
}				t_opts;

#endif
