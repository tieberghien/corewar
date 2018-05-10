/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syboeuf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 16:35:43 by syboeuf           #+#    #+#             */
/*   Updated: 2018/05/10 21:30:04 by etieberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		parsing_arg_b(char *str, t_opts *opts, int *j, t_champs *champs)
{
	int	k;

	k = 0;
	if (str[k] == '-')
		k++;
	while (str[k] >= '0' && str[k] <= '9')
		k++;
	if (str[k])
		return (ft_printf("not a number\n"));
	if (*j == 1)
	{
		if (opts->s_cycles != 0)
			return (ft_printf("more than 1 dump command\n"));
		opts->s_cycles = ft_atoi(str);
		*j = 0;
	}
	else
	{
		champs[opts->n_players].player_id = ft_atoi(str);
		*j = -1;
	}
	return (0);
}

int		parsing_arg_d(t_champs *champ, t_opts *opts, int *j)
{
	champ[opts->n_players].alive = 0;
	if (champ[opts->n_players].player_id == 0)
		champ[opts->n_players].player_id = -(1 + opts->n_players);
	opts->n_players++;
	if (opts->n_players > MAX_PLAYERS)
		return (ft_printf("too many player\n"));
	*j = 0;
	return (0);
}

int		parsing_arg_c(char *av, t_opts *opts, t_champs *champ, int *j)
{
	char *par;

	if (*j > 0)
	{
		if (parsing_arg_b(av, opts, j, champ))
			return (1);
	}
	else if (!ft_strcmp("-dump", av) && *j == 0)
		*j = 1;
	else if (!ft_strcmp("-n", av) && *j == 0)
		*j = 2;
	else if (!ft_strcmp("-v", av) && *j == 0)
		opts->verbosity = 1;
	else if (ft_strcmp(av, ".cor") &&
			(par = ft_strstr(av, ".cor")) && *j < 1)
	{
		if (ft_strcmp(".cor", par) || par[-1] == '/')
			return (ft_printf("invalid player"));
		champ[opts->n_players].file_name = av;
		parsing_arg_d(champ, opts, j);
	}
	else
		return (ft_printf("invalid player\n"));
	return (0);
}

int		parsing_arg_a(int ac, char **av, t_opts *opts, t_champs *champ)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (++i < ac && opts->n_players < MAX_PLAYERS)
		if (parsing_arg_c(av[i], opts, champ, &j))
			return (1);
	if (1 == ac || opts->n_players == 0 || j != 0)
		return (ft_printf((j == 0) ? "no player\n" : "missing player"));
	return (0);
}

int		main(int ac, char **av)
{
	t_opts			opts;
	t_champs		champs[MAX_PLAYERS];
	t_vm			vm;
	unsigned int	i;
	int				j;

	i = 0;
	j = -1;
	opts.verbosity = 0;
	while (++j < MAX_PLAYERS)
		champs[j].player_id = 0;
	if (MAX_PLAYERS <= 0)
		ft_printf("MAX_PLAYERS not properly defined");
	opts.s_cycles = 0;
	opts.n_players = 0;
	if (parsing_arg_a(ac, av, &opts, champs))
		return (1);
	oc_file(champs, &opts);
	init_vm(champs, &opts, &vm);
	free_vm(&vm, opts);
	return (0);
}
