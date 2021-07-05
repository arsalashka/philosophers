/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 18:23:07 by maearly           #+#    #+#             */
/*   Updated: 2021/06/29 18:23:09 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_cleaner(t_args *args)
{
	int	i;

	if (args->philos)
	{
		i = -1;
		while (++i < args->number_of_philo)
		{
			pthread_mutex_destroy(&args->philos[i].philo_mutex);
			pthread_mutex_destroy(&args->philos[i].eat_mutex);
		}
		free(args->philos);
	}
	if (args->mutex_of_fork)
	{
		i = -1;
		while (++i < args->number_of_philo)
			pthread_mutex_destroy(&args->mutex_of_fork[i]);
		free(args->mutex_of_fork);
	}
	pthread_mutex_destroy(&args->writer_mutex);
	pthread_mutex_destroy(&args->deader_mutex);
	return (1);
}

int	ft_error(char *msg)
{
	write(1, PURPLE, ft_strlen(PURPLE));
	write(1, msg, ft_strlen(msg));
	write(1, RESET, ft_strlen(RESET));
	return (1);
}
