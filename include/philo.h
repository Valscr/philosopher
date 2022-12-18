/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:58:42 by valentin          #+#    #+#             */
/*   Updated: 2022/12/17 17:53:56 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../libft/libft.h"

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philosopher
{
	unsigned int		id;
	unsigned int		nb_eat;
	long long			last_eat;
	struct s_data		*rules;
	pthread_t			thread_id;
}						t_philosopher;

typedef struct s_data
{
	unsigned int	nb_philo;
	unsigned int	time_sleep;
	unsigned int	time_eat;
	unsigned int	time_die;
	int				dead;
	int				nb_dead;
	long long		time_start;
	long long			*forks;
	pthread_mutex_t		*fork;
	pthread_mutex_t		print;
	t_philosopher	*philosophers;
}	t_data;

void	*thread_routine(void *void_philosopher);
int init(t_data *data, char ** argv);

#endif