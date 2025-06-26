/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_setup_threads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 23:06:20 by jgalizio          #+#    #+#             */
/*   Updated: 2025/05/12 18:39:16 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*monitor_th(void *data)
{
	t_table	*table;
	int		i;

	table = data;
	pthread_mutex_lock(&table->locks[SLOCK]);
	pthread_mutex_unlock(&table->locks[SLOCK]);
	ft_usleep(1);
	i = 0;
	while (1)
	{
		i = -1;
		while (++i < table->in[NPH])
		{
			if (check_death(table, &table->philos[i]))
				return (NULL);
			if (check_meals(table, i))
				return (NULL);
			usleep(100);
		}
	}
	return (NULL);
}

static void	*philo_th(void *data)
{
	t_philo	*philo;

	philo = data;
	pthread_mutex_lock(philo->locks[SLOCK]);
	pthread_mutex_unlock(philo->locks[SLOCK]);
	pthread_mutex_lock(philo->locks[PHLOCK]);
	philo->clock[SS] = timestamp();
	philo->clock[SE] = philo->clock[SS];
	if (philo->id % 2)
		ft_usleep(1);
	pthread_mutex_unlock(philo->locks[PHLOCK]);
	while (1)
		if (!(eat(philo) && slp(philo) && think(philo)))
			break ;
	return (NULL);
}

t_bool	setup_threads(t_table *d)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&d->locks[SLOCK]);
	while (++i < d->in[NPH])
		if (pthread_create(&d->philos[i].thread, NULL, philo_th, &d->philos[i]))
			return (f);
	if (pthread_create(&d->monitor, NULL, monitor_th, d))
		return (f);
	pthread_mutex_unlock(&d->locks[SLOCK]);
	return (t);
}
