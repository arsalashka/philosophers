/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 18:00:48 by maearly           #+#    #+#             */
/*   Updated: 2021/06/30 18:00:50 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*get_msg(t_state status)
{
	if (status == TAKE_FORK)
		return ("has taken a fork\n");
	else if (status == EATING)
		return ("is eating\n");
	else if (status == SLEEPING)
		return ("is sleeping\n");
	else if (status == THINKING)
		return ("is thinking\n");
	else if (status == DIED)
		return ("died!\n");
	else if (status == STOP)
		return ("simulation stopped!\n");
	return (NULL);
}

void	print_time(unsigned long start_time)
{
	char	*current_time;

	current_time = ft_itoa(get_time() - start_time);
	write(1, YELLOW, ft_strlen(YELLOW));
	write(1, current_time, ft_strlen(current_time));
	write(1, "ms ", 3);
	write(1, RESET, ft_strlen(RESET));
	free(current_time);
}

void	print_index_philo(char *index_philo)
{
	write(1, BLUE, ft_strlen(BLUE));
	write(1, index_philo, ft_strlen(index_philo));
	write(1, " ", 1);
	write(1, CYAN, ft_strlen(CYAN));
}

void	printer(t_philo *philo, t_state status)
{
	char	*msg;
	char	*index_philo;

	pthread_mutex_lock(&philo->args->writer_mutex);
	if (philo->args->game_over == 1)
		usleep(5000);
	msg = get_msg(status);
	index_philo = ft_itoa(philo->index + 1);
	if (!philo->args->game_over)
	{
		print_time(philo->args->start_time);
		if (status != STOP)
			print_index_philo(index_philo);
		if (status == DIED || status == STOP)
		{
			philo->args->game_over = 1;
			write(1, RESET, ft_strlen(RESET));
			write(1, PURPLE, ft_strlen(PURPLE));
		}
		write(1, msg, ft_strlen(msg));
		write(1, RESET, ft_strlen(RESET));
	}
	pthread_mutex_unlock(&philo->args->writer_mutex);
	free(index_philo);
}
