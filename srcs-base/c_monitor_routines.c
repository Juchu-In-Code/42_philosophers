/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_monitor_routines.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:58:25 by jgalizio          #+#    #+#             */
/*   Updated: 2025/05/12 16:39:48 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_stop_flag(t_table *table)
{
	pthread_mutex_lock(&table->locks[DLOCK]);
	table->stop = t;
	pthread_mutex_unlock(&table->locks[DLOCK]);
}

static void	inform_death(t_table *table, t_philo *philo)
{
	time_t	timestamp;

	pthread_mutex_lock(&table->locks[PLOCK]);
	pthread_mutex_lock(&table->locks[DLOCK]);
	table->stop = t;
	timestamp = time_since(philo->clock[SS]);
	printf("%8lu	%4d %s\n", timestamp, philo->id, ANS_R MSG_D ANS_RES);
	pthread_mutex_unlock(&table->locks[DLOCK]);
	pthread_mutex_unlock(&table->locks[PLOCK]);
}

t_bool	check_death(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(philo->locks[PHLOCK]);
	if (philo->status && time_since(philo->clock[SE]) > table->in[TTD])
	{
		pthread_mutex_unlock(philo->locks[PHLOCK]);
		inform_death(table, philo);
		return (t);
	}
	pthread_mutex_unlock(philo->locks[PHLOCK]);
	return (f);
}

t_bool	check_meals(t_table *table, int i)
{
	int	j;

	pthread_mutex_lock(&table->philocks[i]);
	if (table->philos[i].status & 2)
	{
		pthread_mutex_unlock(&table->philocks[i]);
		j = -1;
		while (++j < table->in[NPH])
		{
			pthread_mutex_lock(&table->philocks[j]);
			if (!(table->philos[j].status & 2))
			{
				pthread_mutex_unlock(&table->philocks[j]);
				return (f);
			}
			pthread_mutex_unlock(&table->philocks[j]);
		}
		set_stop_flag(table);
		return (t);
	}
	else
		pthread_mutex_unlock(&table->philocks[i]);
	return (f);
}
