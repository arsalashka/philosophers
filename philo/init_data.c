/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 18:56:57 by maearly           #+#    #+#             */
/*   Updated: 2021/06/29 18:56:59 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int 	init_mutexes(t_args *args)
{
	int	i;

	args->mutex_of_fork
		= malloc(sizeof(pthread_mutex_t) * args->number_of_philo);
	if (NULL == args->mutex_of_fork)
		return (1);
	i = -1;
	while (++i < args->number_of_philo)
		if (pthread_mutex_init(&args->mutex_of_fork[i], NULL))
			return (1);
	if (pthread_mutex_init(&args->writer_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&args->deader_mutex, NULL))
		return (1);
	pthread_mutex_lock(&args->deader_mutex);
	return (0);
}

int	init_philos(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->number_of_philo)
	{
		args->philos[i].index = i;
		args->philos[i].is_eat = 0;
		args->philos[i].left_fork = i;
		args->philos[i].right_fork = (i + 1) % args->number_of_philo;
		args->philos[i].args = args;
		if (pthread_mutex_init(&args->philos[i].philo_mutex, NULL))
			return (1);
		if (pthread_mutex_init(&args->philos[i].eat_mutex, NULL))
			return (1);
		pthread_mutex_lock(&args->philos[i].eat_mutex);
	}
	return (0);
}

int	init_data(t_args *args)
{
	args->philos = NULL;
	args->mutex_of_fork = NULL;
	args->philos = malloc(sizeof(t_philo) * args->number_of_philo);
	if (NULL == args->philos)
		return (1);
	if (init_philos(args))
		return (1);
	if (init_mutexes(args))
		return (1);
	return (0);
}

int	get_args(t_args *args, int ac, char **av)
{
	args->number_of_philo = ft_atoi(av[1]);
	args->time2die = ft_atoi(av[2]);
	args->time2eat = ft_atoi(av[3]);
	args->time2sleep = ft_atoi(av[4]);
	if (ac == 6)
		args->must_eat = ft_atoi(av[5]);
	else
		args->must_eat = 0;
	args->game_over = 0;
	if (args->number_of_philo < 2 || args->number_of_philo > 200
		|| args->time2die < 60 || args->time2eat < 60
		|| args->time2sleep < 60 || args->must_eat < 0)
		return (1);
	return (0);
}
