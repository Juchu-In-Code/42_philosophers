/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:59:50 by jgalizio          #+#    #+#             */
/*   Updated: 2025/05/15 15:31:10 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (!setup_args(--ac, av, &table))
		return (1);
	if (!setup_program(&table))
		return (table_flip(&table, 2));
	if (!setup_threads(&table))
		return (table_flip(&table, 3));
	return (table_flip(&table, 0));
}
