/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseptimu <aseptimu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 13:03:55 by aseptimu          #+#    #+#             */
/*   Updated: 2022/02/07 16:28:55 by aseptimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_data
{
	int				philos;
	int				die_t;
	int				eat_t;
	int				sleep_t;
	int				eat_num;
	int				kill;
	pthread_mutex_t	all_ate;
	pthread_mutex_t	print;
}				t_data;

typedef struct s_philosophers
{
	int				index;
	long int		start;
	int				ate;
	t_data			*data;
	pthread_mutex_t	get_time_meal;
	long int		meal_time;
	pthread_t		ph;
	pthread_mutex_t	rf;
	pthread_mutex_t	*lf;

}				t_philo;

int			ft_atoi(const char *str);
int			error(char *str);
int			init(int argc, char **argv, t_philo **philo, t_data **data);
void		printer(char *msg, t_philo *philo, long int time);
void		custom_usleep(long int time);
long int	get_time(void);
int			create_threads(t_philo *philo, t_data *data);

#endif