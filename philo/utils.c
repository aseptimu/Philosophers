/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseptimu <aseptimu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 13:08:10 by aseptimu          #+#    #+#             */
/*   Updated: 2022/02/10 18:25:01 by aseptimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	ret;

	ret = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] < '0' || str[i] > '9')
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		ret = ret * 10 + str[i] - '0';
		i++;
	}
	i = 0;
	while (!(*str >= '0' && *str <= '9'))
		str++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (ret > INT_MAX || i > 19 || str[i] != '\0')
		return (0);
	return (ret);
}

long int	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	custom_usleep(long int time)
{
	long int	i;

	i = get_time();
	while (get_time() - i < time)
		usleep(100);
}

void	printer(char *msg, t_philo *philo, long int time)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %d %s\n", get_time() - time, philo->index, msg);
	pthread_mutex_unlock(&philo->data->print);
}
