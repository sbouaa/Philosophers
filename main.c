/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:16:46 by sbouaa            #+#    #+#             */
/*   Updated: 2025/08/15 21:16:40 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_threads(t_data *data)
{
	pthread_t	monitor_thread;
	int			i;

	data->s_time = get_time();
	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].last_meal_time = get_time();
		if (pthread_create(&data->philos[i].thread, NULL,
				philo_routine, &data->philos[i]))
			return (1);
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor, data))
		return (1);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 5 && argc != 6)
		return (printf("Error\n"), 1);
	if (check_args(argv))
		return (printf("Error\n"), 1);
	data = init_data(argv);
	if (!data)
		return (printf("Error\n"), 1);
	if (create_threads(data))
		return (cleanup(data), 1);
	cleanup(data);
	return (0);
}
