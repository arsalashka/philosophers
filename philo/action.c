/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 19:18:24 by maearly           #+#    #+#             */
/*   Updated: 2021/06/30 19:18:25 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->mutex_of_fork[philo->left_fork]);
	printer(philo, TAKE_FORK);
	pthread_mutex_lock(&philo->args->mutex_of_fork[philo->right_fork]);
	printer(philo, TAKE_FORK);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_mutex);
	philo->is_eat = 1;
	philo->last_eat = get_time();
	philo->limit = philo->last_eat + philo->args->time2die;
	printer(philo, EATING);
	usleep(philo->args->time2eat * 1000);
	philo->is_eat = 0;
	pthread_mutex_unlock(&philo->philo_mutex);
	pthread_mutex_unlock(&philo->eat_mutex);
}

void	sleeping(t_philo *philo)
{
	printer(philo, SLEEPING);
	pthread_mutex_unlock(&philo->args->mutex_of_fork[philo->left_fork]);
	pthread_mutex_unlock(&philo->args->mutex_of_fork[philo->right_fork]);
	usleep(philo->args->time2sleep * 1000);
}

void	thinking(t_philo *philo)
{
	printer(philo, THINKING);
}
