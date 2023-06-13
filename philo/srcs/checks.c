/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 20:25:44 by nvaubien          #+#    #+#             */
/*   Updated: 2023/06/12 23:17:06 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	death_check(t_philosopher *philo)
{
	int	i;

	i = 0;
	while (i < philo->rules->nb_philo)
	{
		pthread_mutex_lock(&(philo->rules->state[i]));
		if (philo[i].t_last_meal == -1)
		{
			if (ft_time_diff(philo->rules->first_timestamp, ft_timestamp())
				>= philo->rules->t_die)
			{
				print_state(philo->rules, philo[i].id, "died");
				philo->rules->died = 1;
				pthread_mutex_unlock(&(philo->rules->state[i]));
				return (1);
			}
			pthread_mutex_unlock(&(philo->rules->state[i]));
		}
		else
		{
			if (ft_time_diff(philo[i].t_last_meal, ft_timestamp())
				> philo->rules->t_die)
			{
				print_state(philo->rules, philo[i].id, "died");
				philo->rules->died = 1;
				pthread_mutex_unlock(&(philo->rules->state[i]));
				return (1);
			}
			pthread_mutex_unlock(&(philo->rules->state[i]));
		}
		i++;
	}
	return (0);
}

int	meal_check(t_philosopher *philo)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (philo->rules->nb_eat == -1)
		return (0);
	while (i < philo->rules->nb_philo)
	{
		pthread_mutex_lock(&(philo->rules->state[i]));
		if (philo[i].x_ate >= philo->rules->nb_eat)
			count++;
		else
		{
			pthread_mutex_unlock(&(philo->rules->state[i]));
			break;
		}
		if (count == philo->rules->nb_philo)
		{
			pthread_mutex_unlock(&(philo->rules->state[i]));
			return (1);
		}
		pthread_mutex_unlock(&(philo->rules->state[i]));
		i++;
	}
	return (0);
}