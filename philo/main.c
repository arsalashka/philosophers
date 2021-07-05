/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 16:15:54 by maearly           #+#    #+#             */
/*   Updated: 2021/06/11 16:15:57 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_args	args;

	if (ac < 5 || ac > 6)
		return (ft_error("Invalid number of arguments!\n"));
	if (get_args(&args, ac, av))
		return (ft_error("Get arguments error!\n"));
	if (init_data(&args))
		return (ft_cleaner(&args) && ft_error("Initialization failed!\n"));
	if (open_threads(&args))
		return (ft_cleaner(&args) && ft_error("Threads error!\n"));
	pthread_mutex_lock(&args.deader_mutex);
	pthread_mutex_unlock(&args.deader_mutex);
	ft_cleaner(&args);
	return (0);
}
