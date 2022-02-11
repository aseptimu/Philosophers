/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseptimu <aseptimu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 13:08:10 by aseptimu          #+#    #+#             */
/*   Updated: 2022/02/11 17:56:55 by aseptimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[j])
		j++;
	if (dstsize == 0)
		return (j);
	while (dstsize - 1)
	{
		dst[i] = src[i];
		if (src[i] == 0 || dst[i] == 0)
			return (j);
		i++;
		dstsize--;
	}
	dst[i] = '\0';
	return (j);
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
	sem_wait(philo->data->printf);
	printf("%ld %d %s\n", get_time() - time, philo->index, msg);
	sem_post(philo->data->printf);
}
