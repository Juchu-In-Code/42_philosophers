/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_print_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:10:42 by jgalizio          #+#    #+#             */
/*   Updated: 2025/05/05 10:37:05 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	check_print(t_philo *philo, uint64_t timestamp, char *msg)
{
	pthread_mutex_lock(philo->locks[PLOCK]);
	if (!still_alive(philo))
	{
		pthread_mutex_unlock(philo->locks[PLOCK]);
		return (f);
	}
	printf("%8lu	%4d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(philo->locks[PLOCK]);
	return (t);
}
