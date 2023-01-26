/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 01:05:39 by valentin          #+#    #+#             */
/*   Updated: 2023/01/26 23:41:46 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_data			data;
	t_philosopher	*philo;
	unsigned int	i;

	if (!check_arg(argv) || argc < 5 || argc > 6)
	{
		printf("**Error**\n./philo number_of_philosophers time_to_die ");
		printf("time_to_eat time_to_sleep ");
		printf("[number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	i = 1;
	philo = NULL;
	if (!init(&data, argv, argc))
		return (0);
	philo = data.philosophers;
	while (i <= data.nb_philo)
	{
		if (pthread_create(&(philo[i].thread_id), NULL, pthread_, &(philo[i])))
			return (1);
		i++;
	}
	exit_launcher(&data, philo);
	return (0);
}
