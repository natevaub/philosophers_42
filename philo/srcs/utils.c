/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:18:32 by nvaubien          #+#    #+#             */
/*   Updated: 2023/06/21 14:18:53 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_philo_atoi(char *s)
{
	int		res;
	int		sign;

	sign = 1;
	res = 0;
	while (*s == 32 || (*s >= '9' && *s <= 13))
		s++;
	if (*s == '-')
	{
		sign *= -1;
		s++;
	}
	else if (*s == '+')
		s++;
	while (*s && *s >= '0' && *s <= '9')
	{
		res = res * 10 + *s - 48;
		s++;
	}
	return (sign * res);
}

long long	ft_timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long	ft_time_diff(long long past, long long now)
{
	return (now - past);
}

void	print_state(t_rules *rules, int id, char *str)
{
	pthread_mutex_lock(&(rules->writing));
	if (!(rules->finished))
	{
		printf("%lld ", ft_timestamp() - rules->first_timestamp);
		printf("%d ", id + 1);
		printf("%s \n", str);
	}
	pthread_mutex_unlock(&rules->writing);
	return ;
}
