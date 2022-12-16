/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 01:05:39 by valentin          #+#    #+#             */
/*   Updated: 2022/12/16 23:19:16 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

long long	instant(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void		print(t_data *rules, int id, char *string)
{
	pthread_mutex_lock(&(rules->print));
	if (string)
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

void		smart_sleep(long long time, t_data *rules, t_philosopher *philo)
{
	long long i;

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
		usleep(50);
	}
}

void	*thread_routine(void *void_philosopher)
{
	t_philosopher	*philo;
	t_data			*rules;
	int				i;

	philo = (t_philosopher *)void_philosopher;
	rules = philo->rules;
	i = 0;
	while (philo->nb_eat > 0)
	{
		if (rules->dead == 1)
				return (NULL);
		if (i == 0)
		{	
			if (philo->id == 1 || philo->id % 2 == 1)
			{
				pthread_mutex_lock(&(rules->fork[philo->id]));
				print(rules, philo->id, "has taken left fork");
				pthread_mutex_lock(&(rules->fork[philo->id + 1]));
				print(rules, philo->id, "has taken right fork");
				print(rules, philo->id, "is eating");
				rules->forks[philo->id] = instant();
				rules->forks[philo->id + 1] = instant();
				philo->last_eat = instant();
				smart_sleep(rules->time_eat, rules, philo);
				philo->nb_eat--;
				/*printf("Philosopher [%d] has put forks [%d] on the table\n", philo->id, philo->id);*/
				pthread_mutex_unlock(&(rules->fork[philo->id]));
				/*printf("Philosopher [%d] has put forks [%d] on the table\n", philo->id, philo->id + 1);*/
				pthread_mutex_unlock(&(rules->fork[philo->id + 1]));
				if (rules->dead == 1)
					return (NULL);
				print(rules, philo->id, "is sleeping");
				smart_sleep(rules->time_sleep , rules, philo);
				print(rules, philo->id, "is thinking");
			}
		}
		else if (philo->id == rules->nb_philo)
		{	
			if (rules->time_eat - (instant() - rules->forks[philo->id]) > 0)
				smart_sleep(rules->time_eat - (instant() - rules->forks[philo->id]), rules, philo);
			if (rules->time_eat - (instant() - rules->forks[1]) > 0)
				smart_sleep(rules->time_eat - (instant() - rules->forks[1]), rules, philo);
			pthread_mutex_lock(&(rules->fork[philo->id]));
			print(rules, philo->id, "has taken left fork");
			pthread_mutex_lock(&(rules->fork[1]));
			print(rules, philo->id, "has taken right fork");
			print(rules, philo->id, "is eating");
			rules->forks[philo->id] = instant();
			rules->forks[1] = instant();
			philo->last_eat = instant();
			smart_sleep(rules->time_eat, rules, philo);
			philo->nb_eat--;
			/*printf("Philosopher [%d] has put forks [%d] on the table\n", philo->id, philo->id);*/
			pthread_mutex_unlock(&(rules->fork[philo->id]));
			/*printf("Philosopher [%d] has put forks [%d] on the table\n", philo->id, 1);*/
			pthread_mutex_unlock(&(rules->fork[1]));
			if (rules->dead == 1)
				return (NULL);
			print(rules, philo->id, "is sleeping");
			smart_sleep(rules->time_sleep, rules, philo);
			print(rules, philo->id, "is thinking");
		}
		else
		{
			/*printf("time rest die =%lld\n", rules->time_die - (instant() - philo->last_eat));*/
			/*printf("test = %lld\n", rules->time_die - (instant() - rules->forks[philo->id]));
			printf("time rest eat fork left =%lld\n", rules->time_eat - (instant() - rules->forks[philo->id]));
			printf("time rest eat fork right =%lld\n", rules->time_eat - (instant() - rules->forks[philo->id + 1]));*/
			if (rules->dead == 1)
				return (NULL);
			if (rules->time_eat - (instant() - rules->forks[philo->id]) > 0)
				smart_sleep(rules->time_eat - (instant() - rules->forks[philo->id]), rules, philo);
			if (rules->time_eat - (instant() - rules->forks[philo->id + 1]) > 0)
				smart_sleep(rules->time_eat - (instant() - rules->forks[philo->id + 1]), rules, philo);
			pthread_mutex_lock(&(rules->fork[philo->id]));
			print(rules, philo->id, "has taken left fork");
			pthread_mutex_lock(&(rules->fork[philo->id + 1]));
			print(rules, philo->id, "has taken right fork");
			print(rules, philo->id, "is eating");
			rules->forks[philo->id] = instant();
			rules->forks[philo->id + 1] = instant();
			philo->last_eat = instant();
			smart_sleep(rules->time_eat, rules, philo);
			philo->nb_eat--;
			/*printf("Philosopher [%d] has put forks [%d] on the table\n", philo->id, philo->id);*/
			pthread_mutex_unlock(&(rules->fork[philo->id]));
			/*printf("Philosopher [%d] has put forks [%d] on the table\n", philo->id, philo->id + 1);*/
			pthread_mutex_unlock(&(rules->fork[philo->id + 1]));
			if (rules->dead == 1)
				return (NULL);
			print(rules, philo->id, "is sleeping");
			smart_sleep(rules->time_sleep, rules, philo);
			print(rules, philo->id, "is thinking");
		}
	i++;
	}
	return (NULL);
}

int	init_mutex(t_data *rules)
{
	int	i;

	i = rules->nb_philo + 1;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(rules->fork[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(rules->print), NULL))
		return (1);
	return (0);
}

int init(t_data *data, char ** argv)
{
	unsigned int	i;

	data->forks = malloc(sizeof(int) * (ft_atoi(argv[1]) + 1));
	data->philosophers = malloc(sizeof(t_philosopher) * (ft_atoi(argv[1]) + 2));
	data->fork = malloc(sizeof(pthread_mutex_t) * (ft_atoi(argv[1]) + 2));
	data->dead = 0;
	data->nb_dead = 0;
	data->time_start = instant();
	data->nb_philo = ft_atoi(argv[1]);
	i = data->nb_philo + 1;
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	init_mutex(data);
	while (--i > 0)
	{
		data->forks[i] = instant();
		data->philosophers[i].id = i;
		data->philosophers[i].rules = data;
		data->philosophers[i].last_eat = instant();
		data->philosophers[i].nb_eat = ft_atoi(argv[5]);
	}
	return (0);
}

void	exit_launcher(t_data *rules, t_philosopher *philos)
{
	unsigned int	i;

	i = -1;
	while (++i < rules->nb_philo)
		pthread_join(philos[i].thread_id, NULL);
	i = -1;
	while (++i < rules->nb_philo)
		pthread_mutex_destroy(&(rules->fork[i]));
	pthread_mutex_destroy(&(rules->print));
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philosopher   *philo;
	unsigned int         i;

	if (argc > 6)
		return (0);
	i = 1;
	philo = NULL;
	init(&data, argv);
	philo = data.philosophers;
	while (i <= data.nb_philo)
	{
		if (pthread_create(&(philo[i].thread_id), NULL, thread_routine, &(philo[i])))
			return (1);
		/*phi[i].t_last_meal = timestamp();*/
		i++;
	}
	exit_launcher(&data, philo);
	return (0);
}
