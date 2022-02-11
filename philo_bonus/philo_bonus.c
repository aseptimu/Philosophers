/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseptimu <aseptimu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 19:59:55 by aseptimu          #+#    #+#             */
/*   Updated: 2022/02/11 18:59:35 by aseptimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_cleaner(t_philo *philo)
{
	sem_close(philo->data->ate);
	sem_close(philo->data->forks);
	sem_close(philo->data->printf);
	sem_close(philo->data->waiter);
	free(philo->data);
}

int	error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(2, str, i);
	write(2, "\n", 1);
	return (1);
}

int	forker(t_philo *philo, t_data *data, pid_t *pid)
{
	int	i;

	i = 0;
	while (i < data->philos)
	{
		*pid = fork();
		philo[i].pid = *pid;
		if (*pid == 0)
			philo_start(&philo[i]);
		else if (*pid == -1)
		{
			ft_cleaner(philo);
			free(philo);
			return (error("fork fail"));
		}
		i++;
	}	
	return (0);
}

int	ft_norma(t_philo *philo)
{
	ft_cleaner(philo);
	free(philo);
	return (0);
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	int		i;
	t_data	*data;
	t_philo	*philo;	
	int		status;

	if (argc != 5 && argc != 6)
		return (error("Not enough arguments"));
	status = 0;
	philo = NULL;
	data = NULL;
	if (init(argc, argv, &philo, &data) == 1)
		return (1);
	if (forker(philo, data, &pid) == 1)
		return (1);
	while (pid > 0 && WEXITSTATUS(status) != 20)
		pid = waitpid(-1, &status, 0);
	i = 0;
	while (i < data->philos && WEXITSTATUS(status) == 20)
	{
		if (pid != philo[i].pid)
			kill(philo[i].pid, SIGKILL);
		i++;
	}
	return (ft_norma(philo));
}
