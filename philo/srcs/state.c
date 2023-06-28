/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:11:44 by nvaubien          #+#    #+#             */
/*   Updated: 2023/06/28 11:25:19 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philosopher	get_philo(t_philosopher *philo, int direction)
{
	int				j;
	int				n_philo;
	t_philosopher	to_get;

	pthread_mutex_lock(&(philo->rules->lock));
	j = philo->id;
	n_philo = philo->rules->nb_philo;
	if (direction)
		j += 1;
	else
		j -= 1;
	if (j < 0)
	{
		to_get = philo->rules->philosopher[n_philo - 1];
		pthread_mutex_unlock(&(philo->rules->lock));
		return (to_get);
	}
	else
	{
		to_get = philo->rules->philosopher[j % n_philo];
		pthread_mutex_unlock(&(philo->rules->lock));
		return (to_get);
	}
}

void	thinking_state1(t_philosopher *philo)
{
	if (philo->is_thinking == 1)
	{
		if (philo->id % 2 == 0)
		{
			while (get_philo(philo, 1).t_last_meal < philo->t_last_meal)
			{
			}
			pthread_mutex_lock(&(philo->rules->forks[philo->right_fork]));
			print_state(philo->rules, philo->id, "has taken a fork");
			while (get_philo(philo, 0).t_last_meal < philo->t_last_meal)
			{
			}
			pthread_mutex_lock(&(philo->rules->forks[philo->left_fork]));
			print_state(philo->rules, philo->id, "has taken a fork");
		}
		else
			thinking_state2(philo);
		pthread_mutex_lock(&(philo->rules->lock));
		philo->is_eating = 1;
		philo->is_thinking = 0;
		pthread_mutex_unlock(&(philo->rules->lock));
	}
}

void	thinking_state2(t_philosopher *philo)
{
	if (philo->is_thinking == 1 && philo->id % 2 != 0)
	{
		while (get_philo(philo, 0).t_last_meal < philo->t_last_meal)
		{
		}
		pthread_mutex_lock(&(philo->rules->forks[philo->left_fork]));
		print_state(philo->rules, philo->id, "has taken a fork");
		while (get_philo(philo, 1).t_last_meal < philo->t_last_meal)
		{
		}
		pthread_mutex_lock(&(philo->rules->forks[philo->right_fork]));
		print_state(philo->rules, philo->id, "has taken a fork");
	}
}

void	eating_state(t_philosopher *philo)
{
	if (philo->is_eating == 1)
	{
		pthread_mutex_lock(&(philo->rules->lock));
		philo->t_last_meal = ft_timestamp();
		pthread_mutex_unlock(&(philo->rules->lock));
		print_state(philo->rules, philo->id, "is eating");
		usleep(philo->rules->t_eat * 1000);
		pthread_mutex_unlock(&(philo->rules->forks[philo->right_fork]));
		pthread_mutex_unlock(&(philo->rules->forks[philo->left_fork]));
		pthread_mutex_lock(&(philo->rules->lock));
		philo->x_ate++;
		philo->is_eating = 0;
		philo->is_sleeping = 1;
		pthread_mutex_unlock(&(philo->rules->lock));
	}
}

void	sleeping_state(t_philosopher *philo)
{
	pthread_mutex_lock(&(philo->rules->lock));
	if (philo->is_sleeping)
	{
		pthread_mutex_unlock(&(philo->rules->lock));
		print_state(philo->rules, philo->id, "is sleeping");
		usleep(philo->rules->t_sleep * 1000);
		pthread_mutex_lock(&(philo->rules->lock));
		philo->is_sleeping = 0;
		philo->is_thinking = 1;
		pthread_mutex_unlock(&(philo->rules->lock));
		print_state(philo->rules, philo->id, "is thinking");
	}
	else
	{
		pthread_mutex_unlock(&(philo->rules->lock));
	}
}
