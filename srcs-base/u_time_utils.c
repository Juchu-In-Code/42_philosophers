/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_time_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 01:19:06 by jgalizio          #+#    #+#             */
/*   Updated: 2025/05/09 01:34:30 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	timestamp(void)
{
	t_time	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

time_t	time_since(time_t time)
{
	return ((timestamp() - time));
}

void	ft_usleep(time_t wait)
{
	int	i;

	i = -1;
	while (++i < 4)
		usleep((wait * 1000) / 4);
}

t_bool	wait(t_philo *philo, time_t time)
{
	if (time > philo->times[TTD])
	{
		ft_usleep(philo->times[TTD] + 1);
		return (f);
	}
	ft_usleep(time);
	return (t);
}
