/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:58:42 by valentin          #+#    #+#             */
/*   Updated: 2022/12/19 02:30:25 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philosopher
{
	unsigned int		id;
	unsigned int		nb_eat;
	int					mutex_autorise;
	long long			last_eat;
	struct s_data		*rules;
	pthread_t			thread_id;
}						t_philosopher;

typedef struct s_data
{
	unsigned int		nb_philo;
	unsigned int		time_sleep;
	unsigned int		time_eat;
	unsigned int		time_die;
	int					dead;
	int					nb_dead;
	long long			time_start;
	long long			*forks;
	pthread_mutex_t		*fork;
	pthread_mutex_t		print;
	t_philosopher		*philosophers;
}	t_data;

int			init(t_data *data, char **argv, int argc);
int			init_mutex(t_data *rules);
void		init_bis(t_data *data, char **argv, int argc);
int			check_arg(char **argv);
int			diner(t_data *rules, t_philosopher *philo, int philo1, int philo2);
int			pthread_run(t_data *rules, t_philosopher *philo, unsigned int i);
void		*pthread_(void *void_philosopher);
void		exit_launcher(t_data *rules, t_philosopher *philos);
long long	instant(void);
void		print(t_data *rules, int id, char *string);
long long	time_diff(long long past, long long pres);
void		smart_sleep(long long time, t_data *rules, t_philosopher *philo);
int			check_mutex(t_data *ru, t_philosopher *phi);
int			ft_isdigit(unsigned char c);
int			ft_atoi(const char *str);

#endif