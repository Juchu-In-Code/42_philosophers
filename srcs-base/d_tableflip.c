/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_tableflip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:18:30 by jgalizio          #+#    #+#             */
/*   Updated: 2025/05/15 15:39:05 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	table_flip(t_table *table, int err)
{
	int	i;

	i = -1;
	pthread_join(table->monitor, NULL);
	while (++i < table->in[NPH])
		pthread_join(table->philos[i].thread, NULL);
	i = -1;
	while (++i < table->in[NPH])
	{
		pthread_mutex_destroy(&table->philocks[i]);
		pthread_mutex_destroy(&table->forks[i]);
	}
	pthread_mutex_destroy(&table->locks[SLOCK]);
	pthread_mutex_destroy(&table->locks[DLOCK]);
	pthread_mutex_destroy(&table->locks[PLOCK]);
	free(table->forks);
	free(table->philos);
	free(table->philocks);
	return (err);
}
