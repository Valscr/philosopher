/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 02:14:53 by valentin          #+#    #+#             */
/*   Updated: 2022/12/20 17:15:50 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long long	instant(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long	instant_micro(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000000) + t.tv_usec);
}

void	print(t_data *rules, int id, char *string)
{
	pthread_mutex_lock(&(rules->print));
	if (!rules->nb_dead)
	{
		printf("%lld %d %s\n", instant() - rules->time_start, id, string);
	}
	pthread_mutex_unlock(&(rules->print));
	return ;
}

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

void	smart_sleep(long long time, t_data *rules, t_philosopher *philo)
{
	long long	i;

	i = instant();
	while (!(rules->dead))
	{
		if (instant() - philo->last_eat > rules->time_die)
		{
			rules->dead = 1;
			print(rules, philo->id, "is dead");
			rules->nb_dead = philo->id;
			break ;
		}
		if (time_diff(i, instant()) >= time)
			break ;
		usleep(100);
	}
}
