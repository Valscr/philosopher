/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 02:17:16 by valentin          #+#    #+#             */
/*   Updated: 2023/01/26 23:59:35 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	diner(t_data *rules, t_philosopher *philo, int philo1, int philo2)
{
	if (!time_mutex(rules, philo, philo1, philo2))
		return (0);
	pthread_mutex_lock(&(rules->fork[philo1]));
	print(rules, philo1, "has taken a fork");
	pthread_mutex_lock(&(rules->fork[philo2]));
	print(rules, philo1, "has taken a fork");
	print(rules, philo1, "is eating");
	philo->last_eat = instant();
	rules->forks[philo1] = instant();
	rules->forks[philo2] = instant();
	smart_sleep(rules->time_eat, rules, philo);
	philo->nb_eat--;
	pthread_mutex_unlock(&(rules->fork[philo1]));
	pthread_mutex_unlock(&(rules->fork[philo2]));
	if (rules->dead == 1 || (rules->count && philo->nb_eat <= 0))
		return (0);
	print(rules, philo1, "is sleeping");
	smart_sleep(rules->time_sleep, rules, philo);
	if (rules->dead == 1)
		return (0);
	print(rules, philo1, "is thinking");
	return (1);
}

int	pthread_run2(t_data *rules, t_philosopher *philo)
{
	if (philo->id == rules->nb_philo)
	{
		if (!diner(rules, philo, philo->id, 1))
			return (0);
	}
	else
	{
		if (!diner(rules, philo, philo->id, philo->id + 1))
			return (0);
	}
	return (1);
}

int	pthread_run(t_data *rules, t_philosopher *philo, unsigned int i)
{
	while (1)
	{
		if (i == 0)
		{
			if (philo->id == 1 || (philo->id % 2 == 1))
			{
				if (!pthread_run2(rules, philo))
					return (0);
			}
			else
				smart_sleep(rules->time_eat - 1, rules, philo);
		}
		else
			if (!pthread_run2(rules, philo))
				return (0);
		i++;
	}
	return (0);
}

void	*pthread_(void *void_philosopher)
{
	t_philosopher	*philo;
	t_data			*rules;
	int				i;

	philo = (t_philosopher *)void_philosopher;
	rules = philo->rules;
	i = 0;
	pthread_run(rules, philo, i);
	return (NULL);
}

void	exit_launcher(t_data *rules, t_philosopher *philos)
{
	unsigned int	i;

	i = 0;
	while (i++ < rules->nb_philo)
		pthread_join(philos[i].thread_id, NULL);
	i = 0;
	while (i++ < rules->nb_philo)
		pthread_mutex_destroy(&(rules->fork[i]));
	pthread_mutex_destroy(&(rules->print));
	free(rules->forks);
	free(rules->fork);
	free(rules->philosophers);
}
