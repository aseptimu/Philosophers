/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseptimu <aseptimu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 13:03:15 by aseptimu          #+#    #+#             */
/*   Updated: 2022/02/07 17:42:11 by aseptimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks_eat(t_philo *philo)
{
	if (philo->index % 2 == 1)
	{
		pthread_mutex_lock(philo->lf);
		printer("has taken a fork", philo, philo->start);
		pthread_mutex_lock(&philo->rf);
		printer("has taken a fork", philo, philo->start);
	}
	else
	{
		pthread_mutex_lock(&philo->rf);
		printer("has taken a fork", philo, philo->start);
		pthread_mutex_lock(philo->lf);
		printer("has taken a fork", philo, philo->start);
	}
	printer("is eating", philo, philo->start);
	pthread_mutex_lock(&philo->get_time_meal);
	philo->meal_time = get_time();
	pthread_mutex_unlock(&philo->get_time_meal);
	custom_usleep(philo->data->eat_t);
}

int	check_sleep_think(t_philo *philo)
{
	if (philo->index % 2 == 1)
	{
		pthread_mutex_unlock(&philo->rf);
		pthread_mutex_unlock(philo->lf);
	}
	else
	{
		pthread_mutex_unlock(philo->lf);
		pthread_mutex_unlock(&philo->rf);
	}
	philo->ate++;
	if (philo->ate == philo->data->eat_num)
	{
		pthread_mutex_lock(&philo->data->all_ate);
		philo->index = -1;
		philo->data->kill++;
		pthread_mutex_unlock(&philo->data->all_ate);
		return (0);
	}
	printer("is sleeping", philo, philo->start);
	custom_usleep(philo->data->sleep_t);
	usleep(200);
	printer("is thinking", philo, philo->start);
	return (1);
}

void	*threader(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	philo->start = get_time();
	pthread_mutex_lock(&philo->get_time_meal);
	philo->meal_time = philo->start;
	pthread_mutex_unlock(&philo->get_time_meal);
	if (philo->index % 2 == 0)
		usleep(100);
	while (1)
	{
		take_forks_eat(philo);
		if (check_sleep_think(philo) == 0)
			return (0);
	}
	return (0);
}

void	start_monitor(t_philo *philo, t_data *data)
{
	int	i;

	usleep(100);
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&data->all_ate);
		if (data->kill == data->philos)
			break ;
		pthread_mutex_unlock(&data->all_ate);
		pthread_mutex_lock(&philo[i].get_time_meal);
		if (get_time() - philo[i].meal_time > data->die_t \
			&& philo[i].index != -1)
		{
			pthread_mutex_lock(&data->print);
			printf("%ld %d %s\n", get_time() - philo[i].start, \
					philo[i].index, "died");
			break ;
		}
		pthread_mutex_unlock(&philo[i].get_time_meal);
		i++;
		if (i == data->philos)
			i = 0;
	}
}

int	create_threads(t_philo *philo, t_data *data)
{
	int	i;
	int	err;

	i = 0;
	while (i < philo[0].data->philos)
	{
		if (pthread_create(&philo[i].ph, NULL, &threader, &philo[i]) != 0)
			return (error("thread create error"));
		i++;
	}
	i = 0;
	start_monitor(philo, data);
	while (i < philo[0].data->philos)
	{
		err = pthread_detach(philo[i].ph);
		if (err != 0)
			return (error("thread detach error"));
		i++;
	}
	return (0);
}
