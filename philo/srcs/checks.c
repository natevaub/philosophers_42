/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 20:25:44 by nvaubien          #+#    #+#             */
/*   Updated: 2023/06/27 15:28:45 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	handle_death(t_philosopher *philo, int i)
{
	int	end;

	end = 0;
	print_state(philo->rules, philo[i].id, "died");
	pthread_mutex_lock(&(philo->rules->lock));
	philo->rules->finished = 1;
	philo->rules->died = 1;
	pthread_mutex_unlock(&(philo->rules->lock));
	end = 1;
	return (end);
}

int	death_check(t_philosopher *philo)
{
	int	i;

	i = 0;
	while (i < philo->rules->nb_philo)
	{
		pthread_mutex_lock(&(philo->rules->lock));
		if (philo[i].t_last_meal == -1)
		{
			if (ft_time_diff(philo->rules->first_timestamp, ft_timestamp())
				>= philo->rules->t_die)
			{
				pthread_mutex_unlock(&(philo->rules->lock));
				handle_death(philo, i);
				return 1;
			}
			pthread_mutex_unlock(&(philo->rules->lock));
		}
		else
		{
			if (ft_time_diff(philo[i].t_last_meal, ft_timestamp())
				> philo->rules->t_die)
			{
				pthread_mutex_unlock(&(philo->rules->lock));
				handle_death(philo, i);
				return 1;
			}
			pthread_mutex_unlock(&(philo->rules->lock));
		}
		i++;
	}
	return (0);
}

int	meal_check(t_philosopher *philo)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	if (philo->rules->nb_eat == -1)
		return (0);
	while (++i < philo->rules->nb_philo)
	{
		pthread_mutex_lock(&(philo->rules->lock));
		if (philo[i].x_ate >= philo->rules->nb_eat)
			count++;
		else
		{
			pthread_mutex_unlock(&(philo->rules->lock));
			break ;
		}
		if (count == philo->rules->nb_philo)
		{
			philo->rules->finished = 1;
			pthread_mutex_unlock(&(philo->rules->lock));
			return (1);
		}
		pthread_mutex_unlock(&(philo->rules->lock));
	}
	return (0);
}
