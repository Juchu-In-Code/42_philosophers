/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_setup_program.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:34:26 by jgalizio          #+#    #+#             */
/*   Updated: 2025/05/12 18:19:42 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	setup_philos(t_table *table)
{
	int	i;

	i = -1;
	table->philos = malloc(table->in[NPH] * sizeof(t_philo));
	if (!table->philos)
		return (f);
	while (++i < table->in[NPH])
	{
		table->philos[i].status = 1;
		table->philos[i].id = i + 1;
		table->philos[i].clock[SS] = 0;
		table->philos[i].clock[SE] = 0;
		table->philos[i].meals = table->in[QM];
		table->philos[i].fork[L] = &table->forks[i];
		table->philos[i].fork[R] = &table->forks[(i + 1) % table->in[NPH]];
		table->philos[i].locks[PHLOCK] = &table->philocks[i];
		table->philos[i].locks[PLOCK] = &table->locks[PLOCK];
		table->philos[i].locks[DLOCK] = &table->locks[DLOCK];
		table->philos[i].locks[SLOCK] = &table->locks[SLOCK];
		table->philos[i].times[TTD] = table->in[TTD];
		table->philos[i].times[TTE] = table->in[TTE];
		table->philos[i].times[TTS] = table->in[TTS];
		table->philos[i].stop = &table->stop;
	}
	return (t);
}

static t_bool	setup_locks(t_table *table)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	table->forks = malloc(table->in[NPH] * sizeof(t_mtx));
	table->philocks = malloc(table->in[NPH] * sizeof(t_mtx));
	if (!table->forks || !table->philocks)
		return (f);
	while (++i < table->in[NPH])
		pthread_mutex_init(&table->forks[i], NULL);
	while (++j < table->in[NPH])
		pthread_mutex_init(&table->philocks[j], NULL);
	pthread_mutex_init(&table->locks[PLOCK], NULL);
	pthread_mutex_init(&table->locks[DLOCK], NULL);
	pthread_mutex_init(&table->locks[SLOCK], NULL);
	return (t);
}

t_bool	setup_program(t_table *table)
{
	if (!setup_locks(table) || !setup_philos(table))
		return (f);
	table->stop = f;
	return (t);
}
