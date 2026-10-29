/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 00:32:04 by sbouaa            #+#    #+#             */
/*   Updated: 2025/08/15 01:23:25 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	long long		s_time;
	int				dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	dead_mutex;
	t_philo			*philos;
}	t_data;

int			main(int argc, char **argv);
int			ft_atoi(char *str);
int			check_args(char **argv);
t_data		*init_data(char **argv);
void		cleanup(t_data *data);
long long	get_time(void);
int			ft_usleep(t_data	*data, int ms);
void		print_status(t_philo *philo, char *status);
int			check_death(t_data *data);
void		*philo_routine(void *arg);
void		take_forks(t_philo *philo);
void		eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		*monitor(void *arg);
int			check_all_ate(t_data *data);
int			philosopher_dead(t_philo *philo, long long time);

#endif