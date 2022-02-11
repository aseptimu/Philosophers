/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseptimu <aseptimu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:00:17 by aseptimu          #+#    #+#             */
/*   Updated: 2022/02/11 18:40:05 by aseptimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <signal.h>
# include <limits.h>
# include <semaphore.h>

typedef struct s_data
{
	int		philos;
	int		die_t;
	int		eat_t;
	int		sleep_t;
	int		eat_num;
	sem_t	*ate;
	int		count_ate;
	sem_t	*forks;
	sem_t	*printf;
	sem_t	*waiter;
}				t_data;

typedef struct s_philo
{
	pid_t		pid;
	int			index;
	long int	start;
	int			eat_one;
	long int	meal_time;
	t_data		*data;
}				t_philo;

int			ft_atoi(const char *str);
int			error(char *str);
void		printer(char *msg, t_philo *philo, long int time);
void		custom_usleep(long int time);
long int	get_time(void);
int			init(int argc, char **argv, t_philo **philo, t_data **data);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
void		philo_start(t_philo *philo);
void		ft_cleaner(t_philo *philo);
#endif