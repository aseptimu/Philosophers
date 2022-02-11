/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_live_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseptimu <aseptimu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 17:36:50 by aseptimu          #+#    #+#             */
/*   Updated: 2022/02/11 18:34:19 by aseptimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	check_death(t_philo *philo)
{
	if (get_time() - philo->meal_time > philo->data->die_t)
	{
		sem_wait(philo->data->printf);
		printf("%ld %d %s\n", get_time() - philo->start, philo->index, "died");
		usleep(100);
		ft_cleaner(philo);
		exit(20);
	}
}

void	check_eat(t_philo *philo)
{
	if (philo->data->eat_num != -1)
	{
		philo->eat_one++;
		if (philo->eat_one == philo->data->eat_num)
		{
			ft_cleaner(philo);
			exit(0);
		}
	}
}

void	philo_start(t_philo *philo)
{
	philo->start = get_time();
	philo->meal_time = philo->start;
	while (1)
	{
		sem_wait(philo->data->waiter);
		sem_wait(philo->data->forks);
		check_death(philo);
		printer("has taken a fork", philo, philo->start);
		sem_wait(philo->data->forks);
		printer("has taken a fork", philo, philo->start);
		sem_post(philo->data->waiter);
		check_death(philo);
		printer("is eating", philo, philo->start);
		philo->meal_time = get_time();
		custom_usleep(philo->data->eat_t);
		sem_post(philo->data->forks);
		sem_post(philo->data->forks);
		check_eat(philo);
		check_death(philo);
		printer("is sleeping", philo, philo->start);
		custom_usleep(philo->data->sleep_t);
		usleep(100);
		check_death(philo);
		printer("is thinking", philo, philo->start);
	}
}
