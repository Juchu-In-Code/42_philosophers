/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:46:23 by jgalizio          #+#    #+#             */
/*   Updated: 2025/05/15 15:42:23 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdint.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

/*  __  __                           */
/* |  \/  | __ _  ___ _ __ ___  ___  */
/* | |\/| |/ _` |/ __| '__/ _ \/ __| */
/* | |  | | (_| | (__| | | (_) \__ \ */
/* |_|  |_|\__,_|\___|_|  \___/|___/ */
/* ================================= */

# define ANS_R		"\033[31m"
# define ANS_G		"\033[32m"
# define ANS_U		"\033[34m"
# define ANS_Y		"\033[33m"
# define ANS_C		"\033[36m"
# define ANS_M		"\033[35m"
# define ANS_W		"\033[37m"
# define ANS_RES	"\033[0m"

# define TTD 0
# define TTE 1
# define TTS 2

# define NPH 3
# define QM 4

# define SS 0
# define SE 1

# define L 0
# define R 1

# define PLOCK 0
# define DLOCK 1
# define SLOCK 2
# define PHLOCK 3

# define MSG_F	"has taken a fork"
# define MSG_S	"is sleeping"
# define MSG_T	"is thinking"
# define MSG_E	"is eating"
# define MSG_D	"died"

/*  ____        __ _                  */
/* |  _ \  ___ / _(_)_ __   ___  ___  */
/* | | | |/ _ \ |_| | '_ \ / _ \/ __| */
/* | |_| |  __/  _| | | | |  __/\__ \ */
/* |____/ \___|_| |_|_| |_|\___||___/ */
/* ================================== */

typedef pthread_mutex_t	t_mtx;
typedef struct timeval	t_time;

typedef enum e_bool
{
	f,
	t
}	t_bool;

/*  ____  _                   _        */
/* / ___|| |_ _ __ _   _  ___| |_ ___  */
/* \___ \| __| '__| | | |/ __| __/ __| */
/*  ___) | |_| |  | |_| | (__| |_\__ \ */
/* |____/ \__|_|   \__,_|\___|\__|___/ */
/* =================================== */

typedef struct s_philo
{
	uint32_t	id;
	long		meals;
	uint8_t		status;
	time_t		times[3];
	time_t		clock[2];
	t_mtx		*fork[2];
	t_mtx		*locks[4];
	pthread_t	thread;
	t_bool		*stop;
}	t_philo;

typedef struct s_table
{
	t_bool		stop;
	int			in[5];
	t_mtx		*forks;
	t_mtx		*philocks;
	t_mtx		locks[3];
	t_philo		*philos;
	pthread_t	monitor;
}	t_table;

/*  ____            _        _                          */
/* |  _ \ _ __ ___ | |_ ___ | |_ _   _ _ __   ___  ___  */
/* | |_) | '__/ _ \| __/ _ \| __| | | | '_ \ / _ \/ __| */
/* |  __/| | | (_) | || (_) | |_| |_| | |_) |  __/\__ \ */
/* |_|   |_|  \___/ \__\___/ \__|\__, | .__/ \___||___/ */
/* ==============================|___/|_|============== */

//	 setup args.c
t_bool		setup_args(int ac, char **av, t_table *table);

//	 setup_program.c
t_bool		setup_program(t_table *table);

//	 verify args_utils
int			ft_isdigit(char c);
long		ft_atol(const char *str);
size_t		ft_strlen(const char *s);
t_bool		ft_isnumeric(char *str);

// time utils
t_bool		setup_threads(t_table *d);

// thread routine.c
t_bool		pickup_fork(t_philo *philo, int cont);
t_bool		eat(t_philo *philo);
t_bool		slp(t_philo *philo);
t_bool		think(t_philo *philo);
t_bool		still_alive(t_philo *philo);

//monitor routines.c
t_bool		check_death(t_table *table, t_philo *philo);
t_bool		check_meals(t_table *table, int i);

// time utils
time_t		timestamp(void);
time_t		time_since(time_t time);
void		ft_usleep(time_t wait);
t_bool		wait(t_philo *philo, time_t time);

// print utils
t_bool		check_print(t_philo *philo, uint64_t timestamp, char *msg);

//cleanup
int			table_flip(t_table *table, int err);

// error utils
void		ft_err(char *str);

#endif
