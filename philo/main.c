/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseptimu <aseptimu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 12:47:44 by aseptimu          #+#    #+#             */
/*   Updated: 2022/02/07 17:31:26 by aseptimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_philo *philo, t_data *data)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = data->philos;
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->all_ate);
	free(data);
	while (i < tmp)
	{
		pthread_mutex_destroy(&philo[i].rf);
		pthread_mutex_destroy(&philo[i].get_time_meal);
		i++;
	}
	free(philo);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_data	*data;

	philo = NULL;
	data = NULL;
	if (argc != 5 && argc != 6)
		return (error("Not enough arguments"));
	data = NULL;
	if (init(argc, argv, &philo, &data) == 1)
		return (1);
	if (create_threads(philo, data) == 1)
		return (1);
	free_all(philo, data);
}
