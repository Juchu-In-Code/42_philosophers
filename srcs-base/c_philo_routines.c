/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_philo_routines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:13:34 by jgalizio          #+#    #+#             */
/*   Updated: 2025/05/15 15:42:05 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	still_alive(t_philo *philo)
{
	pthread_mutex_lock(philo->locks[DLOCK]);
	if (*philo->stop == t)
	{
		pthread_mutex_unlock(philo->locks[DLOCK]);
		return (f);
	}
	pthread_mutex_unlock(philo->locks[DLOCK]);
	return (t);
}

t_bool	slp(t_philo *philo)
{
	if (!check_print(philo, time_since(philo->clock[SS]), ANS_C MSG_S ANS_RES))
		return (f);
	return (wait(philo, philo->times[TTS]));
}

t_bool	think(t_philo *philo)
{
	if (!check_print(philo, time_since(philo->clock[SS]), ANS_C MSG_T ANS_RES))
		return (f);
	usleep(100);
	return (t);
}

t_bool	pickup_fork(t_philo *philo, int side)
{
	if (philo->fork[L] == philo->fork[R])
	{
		check_print(philo, time_since(philo->clock[SS]), ANS_G MSG_F ANS_RES);
		ft_usleep(philo->times[TTD]);
		return (f);
	}
	pthread_mutex_lock(philo->fork[side]);
	if (!check_print(philo, time_since(philo->clock[SS]), ANS_G MSG_F ANS_RES))
	{
		pthread_mutex_unlock(philo->fork[side]);
		return (f);
	}
	return (t);
}

t_bool	eat(t_philo *philo)
{
	if (!pickup_fork(philo, philo->id % 2))
		return (f);
	if (!pickup_fork(philo, (philo->id + 1) % 2))
	{
		pthread_mutex_unlock(philo->fork[(philo->id) % 2]);
		return (f);
	}
	if (!check_print(philo, time_since(philo->clock[SS]), ANS_M MSG_E ANS_RES))
	{
		pthread_mutex_unlock(philo->fork[L]);
		pthread_mutex_unlock(philo->fork[R]);
		return (f);
	}
	pthread_mutex_lock(philo->locks[PHLOCK]);
	philo->clock[SE] = timestamp();
	pthread_mutex_unlock(philo->locks[PHLOCK]);
	wait(philo, philo->times[TTE]);
	pthread_mutex_unlock(philo->fork[L]);
	pthread_mutex_unlock(philo->fork[R]);
	pthread_mutex_lock(philo->locks[PHLOCK]);
	if (philo->meals != -1 && !--philo->meals)
		philo->status += 2;
	pthread_mutex_unlock(philo->locks[PHLOCK]);
	return (t);
}
