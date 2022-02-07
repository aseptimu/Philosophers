/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseptimu <aseptimu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:06:07 by aseptimu          #+#    #+#             */
/*   Updated: 2022/02/07 17:46:56 by aseptimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(int argc, char **argv, t_data *data)
{
	int	err;

	err = pthread_mutex_init(&data->print, NULL);
	if (err != 0)
		return (error("mutex init error"));
	err = pthread_mutex_init(&data->all_ate, NULL);
	if (err != 0)
		return (error("mutex init error"));
	data->kill = 0;
	data->philos = ft_atoi(argv[1]);
	data->die_t = ft_atoi(argv[2]);
	data->eat_t = ft_atoi(argv[3]);
	data->sleep_t = ft_atoi(argv[4]);
	data->eat_num = -1;
	if (argc == 6)
		data->eat_num = ft_atoi(argv[5]);
	if (data->philos == 0 || data->die_t == 0 || data->eat_t == 0 \
		|| data->sleep_t == 0 || data->eat_num == 0)
		return (error("Bad args"));
	return (0);
}

int	fill_philo(t_philo **philo, t_data **data, int i)
{
	int	err;

	err = pthread_mutex_init(&(*philo)[i].get_time_meal, NULL);
	if (err != 0)
		return (error("mutex init error"));
	(*philo)[i].index = i + 1;
	(*philo)[i].ate = 0;
	(*philo)[i].data = *data;
	(*philo)[i].meal_time = 0;
	if (i == 0)
		err = pthread_mutex_init(&(*philo)[i].rf, NULL);
	else
	{
		(*philo)[i].lf = &(*philo)[i - 1].rf;
		err = pthread_mutex_init(&(*philo)[i].rf, NULL);
	}
	if (err != 0)
		return (error("mutex init error"));
	return (0);
}

int	init_philo(t_philo **philo, t_data **data)
{
	int	i;

	i = 0;
	(*philo) = (t_philo *)malloc(sizeof(t_philo) * (*data)->philos);
	if (!(*philo))
		return (error("Memory allocate error"));
	(*philo)->ph = 0;
	while (i < (*data)->philos)
	{
		if (fill_philo(philo, data, i) == 1)
			return (1);
		i++;
	}
	(*philo)[0].lf = &(*philo)[(*data)->philos - 1].rf;
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
