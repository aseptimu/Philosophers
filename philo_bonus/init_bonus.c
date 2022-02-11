/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseptimu <aseptimu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:06:07 by aseptimu          #+#    #+#             */
/*   Updated: 2022/02/11 18:33:07 by aseptimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_water_ate(t_data *data)
{
	sem_unlink("waiter");
	data->waiter = sem_open("waiter", O_CREAT, 0644, 1);
	if (data->waiter == SEM_FAILED)
	{
		sem_close(data->forks);
		sem_close(data->printf);
		return (error("Semaphore waiter open fail"));
	}
	sem_unlink("waiter");
	sem_unlink("ate");
	data->ate = sem_open ("ate", O_CREAT, 0644, 1);
	if (data->ate == SEM_FAILED)
	{
		sem_close(data->forks);
		sem_close(data->printf);
		sem_close(data->waiter);
		return (error("Semaphore ate open fail"));
	}
	sem_unlink("ate");
	return (0);
}

int	data_sem_init(t_data *data)
{
	sem_unlink("forks");
	data->forks = sem_open("forks", O_CREAT, 0644, data->philos);
	if (data->forks == SEM_FAILED)
		return (error("Semaphore forks open fail"));
	sem_unlink("forks");
	sem_unlink("printf");
	data->printf = sem_open("printf", O_CREAT, 0644, 1);
	if (data->printf == SEM_FAILED)
	{
		sem_close (data->forks);
		return (error("Semaphore printf open fail"));
	}
	sem_unlink("printf");
	if (init_water_ate(data) == 1)
		return (1);
	return (0);
}

int	init_data(int argc, char **argv, t_data *data)
{
	data->philos = ft_atoi(argv[1]);
	data->die_t = ft_atoi(argv[2]);
	data->eat_t = ft_atoi(argv[3]);
	data->sleep_t = ft_atoi(argv[4]);
	data->eat_num = -1;
	if (argc == 6)
		data->eat_num = ft_atoi(argv[5]);
	data->count_ate = 0;
	if (data->philos == 0 || data->die_t == 0 || data->eat_t == 0 \
		|| data->sleep_t == 0 || data->eat_num == 0)
		return (error("Bad args"));
	if (data_sem_init(data) == 1)
		return (1);
	return (0);
}

int	init_philo(t_philo **philo, t_data **data)
{
	int	i;

	(*philo) = (t_philo *)malloc(sizeof(t_philo) * (*data)->philos);
	if (!(*philo))
		return (error("Memory allocate error"));
	i = 0;
	while (i < (*data)->philos)
	{
		(*philo)[i].pid = 0;
		(*philo)[i].index = i + 1;
		(*philo)[i].start = 0;
		(*philo)[i].eat_one = 0;
		(*philo)[i].meal_time = 0;
		(*philo)[i].data = *data;
		i++;
	}
	return (0);
}

int	init(int argc, char **argv, t_philo **philo, t_data **data)
{
	*data = (t_data *)malloc(sizeof(t_data));
	if (!*data)
		return (error("Malloc error"));
	if (init_data(argc, argv, *data) == 1)
		return (1);
	if (init_philo(philo, data) == 1)
		return (1);
	return (0);
}
