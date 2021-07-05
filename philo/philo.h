/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 16:42:13 by maearly           #+#    #+#             */
/*   Updated: 2021/06/11 16:42:17 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define WHITE "\033[1;97m"
# define BLUE "\033[1;94m"
# define PURPLE "\033[1;35m"
# define CYAN "\033[1;36m"
# define YELLOW "\033[1;33m"
# define RESET "\033[0m"

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef enum e_state
{
	THINKING,
	EATING,
	SLEEPING,
	DIED,
	TAKE_FORK,
	STOP
}	t_state;

struct	s_args;

typedef struct s_philo
{
	int				index;
	int				is_eat;
	unsigned long	limit;
	unsigned long	last_eat;
	int				left_fork;
	int				right_fork;
	struct s_args	*args;
	pthread_mutex_t	philo_mutex;
	pthread_mutex_t	eat_mutex;
}	t_philo;

typedef struct s_args
{
	int				number_of_philo;
	unsigned long	time2die;
	unsigned long	time2eat;
	unsigned long	time2sleep;
	int				must_eat;
	unsigned long	start_time;
	t_philo			*philos;
	pthread_mutex_t	*mutex_of_fork;
	pthread_mutex_t	writer_mutex;
	pthread_mutex_t	deader_mutex;
	int				game_over;
}	t_args;

unsigned long	get_time(void);
int				ft_atoi(const char *str);
size_t			ft_strlen(const char *s);
int				ft_error(char *msg);
int				get_args(t_args *args, int ac, char **av);
int				ft_cleaner(t_args *args);
int				init_data(t_args *args);
int				open_threads(t_args *args);
void			printer(t_philo *philo, t_state status);
char			*ft_itoa(unsigned long n);
char			*ft_strdup(const char *s1);
void			forks(t_philo *philo);
void			eating(t_philo *philo);
void			sleeping(t_philo *philo);
void			thinking(t_philo *philo);

#endif
