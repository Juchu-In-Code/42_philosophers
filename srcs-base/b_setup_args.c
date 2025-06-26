/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_setup_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:10:42 by jgalizio          #+#    #+#             */
/*   Updated: 2025/05/12 18:36:46 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	check_valid(char *arg, int *val)
{
	long	num;
	int		i;

	i = 0;
	if (!arg || !*arg)
		return (f);
	if (arg[i] == '+')
		if (!arg[++i])
			return (f);
	if (!ft_isnumeric(&arg[i]))
		return (f);
	num = ft_atol(arg);
	if (num <= 0 || num > INT_MAX)
		return (f);
	*val = num;
	return (t);
}

t_bool	setup_args(int ac, char **av, t_table *table)
{
	table->in[QM] = -1;
	if ((ac < 4 || ac > 5)
		|| !check_valid(av[1], &table->in[NPH])
		|| !check_valid(av[2], &table->in[TTD])
		|| !check_valid(av[3], &table->in[TTE])
		|| !check_valid(av[4], &table->in[TTS])
		|| (ac == 5 && !check_valid(av[5], &table->in[QM])))
	{
		ft_err(ANS_R"Error: Invalid arguments passed."ANS_RES);
		return (f);
	}
	return (t);
}
