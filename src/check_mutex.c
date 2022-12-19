/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 04:47:11 by valentin          #+#    #+#             */
/*   Updated: 2022/12/19 05:15:05 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_mutex(t_data *ru, t_philosopher *phi, int philo1, int philo2)
{
	if (ru->dead == 1)
		return (0);
	if (ru->time_eat - (instant() - ru->forks[philo1]) > 0)
		smart_sleep(ru->time_eat - (instant() - ru->forks[philo1]), ru, phi);
	if (ru->dead == 1)
		return (0);
	if (ru->nb_philo == 1)
	{
		print(ru, philo1, "has taken a fork");
		smart_sleep(ru->time_die * 2, ru, phi);
		return (0);
	}
	if (ru->time_eat - (instant() - ru->forks[philo2]) > 0)
		smart_sleep(ru->time_eat - (instant() - ru->forks[philo2]), ru, phi);
	if (ru->dead == 1)
		return (0);
	return (1);
}
