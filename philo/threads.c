/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 20:30:12 by maearly           #+#    #+#             */
/*   Updated: 2021/06/29 20:30:15 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*eat_counter(void *params)
{
	t_args	*args;
	int		cnt;
	int		i;

	args = (t_args *)params;
	cnt = -1;
	while (++cnt < args->must_eat)
	{
		i = -1;
		while (++i < args->number_of_philo)
			pthread_mutex_lock(&args->philos[i].eat_mutex);
	}
	printer(&args->philos[0], STOP);
	pthread_mutex_unlock(&args->deader_mutex);
	return (NULL);
}

void	*check_live(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (1)
	{
		pthread_mutex_lock(&philo->philo_mutex);
		if (!philo->is_eat && get_time() > philo->limit)
		{
			printer(philo, DIED);
			pthread_mutex_unlock(&philo->args->deader_mutex);
			pthread_mutex_unlock(&philo->philo_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->philo_mutex);
		usleep(1000);
	}
	return (NULL);
}

void	*threads(void *param)
{
	t_philo		*philo;
	pthread_t	thread;

	philo = (t_philo *)param;
	philo->last_eat = get_time();
	philo->limit = philo->last_eat + philo->args->time2die;
	if (pthread_create(&thread, NULL, &check_live, param) != 0)
		return ((void *)1);
	pthread_detach(thread);
	while (1)
	{
		forks(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

int 	open_threads(t_args *args)
{
	pthread_t	thread;
	int			i;
	void		*philo;

	args->start_time = get_time();
	if (args->must_eat > 0)
	{
		if (pthread_create(&thread, NULL, &eat_counter, (void *)args) != 0)
			return (1);
		if (pthread_detach(thread) != 0)
			return (1);
	}
	i = -1;
	while (++i < args->number_of_philo)
	{
		philo = (void *)(&args->philos[i]);
		if (pthread_create(&thread, NULL, &threads, philo) != 0)
			return (1);
		if (pthread_detach(thread) != 0)
			return (1);
		usleep (100);
	}
	return (0);
}
