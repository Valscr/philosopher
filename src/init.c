/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 02:15:43 by valentin          #+#    #+#             */
/*   Updated: 2022/12/19 04:08:01 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_mutex(t_data *rules)
{
	int	i;

	i = rules->nb_philo + 1;
	while (--i > 0)
	{
		if (pthread_mutex_init(&(rules->fork[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(rules->print), NULL))
		return (1);
	return (0);
}

void	init_bis(t_data *data, char **argv, int argc)
{
	unsigned int	i;

	i = data->nb_philo + 1;
	while (--i > 0)
	{
		data->forks[i] = 0;
		data->philosophers[i].id = i;
		data->philosophers[i].rules = data;
		data->philosophers[i].last_eat = instant();
		data->philosophers[i].mutex_autorise = 0;
		if (argc == 5)
			data->philosophers[i].nb_eat = 100000;
		else
			data->philosophers[i].nb_eat = ft_atoi(argv[5]);
	}
}

int	init(t_data *data, char **argv, int argc)
{
	data->forks = malloc(sizeof(long long) * (ft_atoi(argv[1]) + 2));
	if (!data->forks)
		return (0);
	data->philosophers = malloc(sizeof(t_philosopher) * (ft_atoi(argv[1]) + 2));
	if (!data->philosophers)
		return (0);
	data->fork = malloc(sizeof(pthread_mutex_t) * (ft_atoi(argv[1]) + 2));
	if (!data->fork)
		return (0);
	data->dead = 0;
	data->nb_dead = 0;
	data->time_start = instant();
	data->nb_philo = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	init_mutex(data);
	init_bis(data, argv, argc);
	return (1);
}

int	check_arg(char **argv)
{
	int	i;
	int	y;

	y = 1;
	while (argv[y])
	{
		i = 0;
		if ((!ft_isdigit(argv[y][i]) && argv[y][0] != '+')
			|| ft_atoi(argv[y]) <= 0)
			return (0);
		i++;
		while (argv[y][i] != '\0')
		{
			if (!ft_isdigit(argv[y][i]))
				return (0);
			i++;
		}
		y++;
	}
	return (1);
}
