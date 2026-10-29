/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:17:25 by sbouaa            #+#    #+#             */
/*   Updated: 2025/08/15 20:55:07 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_death(t_data *data, int id)
{
	pthread_mutex_lock(&data->print_mutex);
	printf("%lld %d died\n", get_time() - data->s_time, id);
	pthread_mutex_unlock(&data->print_mutex);
}

int	philosopher_dead(t_philo *philo, long long time)
{
	pthread_mutex_lock(&philo->data->meal_mutex);
	if (time - philo->last_meal_time >= philo->data->time_to_die)
	{
		pthread_mutex_unlock(&philo->data->meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->meal_mutex);
	return (0);
}

int	check_all_ate(t_data *data)
{
	int	i;
	int	finished;

	if (data->max_meals == -1)
		return (0);
	i = 0;
	finished = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->meal_mutex);
		if (data->philos[i].meals_eaten >= data->max_meals)
			finished++;
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
	}
	if (finished == data->num_philos)
	{
		pthread_mutex_lock(&data->dead_mutex);
		data->dead = 1;
		pthread_mutex_unlock(&data->dead_mutex);
		return (1);
	}
	return (0);
}

static int	check_philosopher_death(t_data *data, int i)
{
	long long	time;

	time = get_time();
	if (philosopher_dead(&data->philos[i], time))
	{
		print_death(data, data->philos[i].id);
		pthread_mutex_lock(&data->dead_mutex);
		data->dead = 1;
		pthread_mutex_unlock(&data->dead_mutex);
		return (1);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->num_philos)
		{
			if (check_philosopher_death(data, i))
				return (NULL);
			i++;
		}
		if (check_all_ate(data))
			break ;
		usleep(1000);
	}
	return (NULL);
}
