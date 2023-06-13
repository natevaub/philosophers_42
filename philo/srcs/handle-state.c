/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle-state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:11:44 by nvaubien          #+#    #+#             */
/*   Updated: 2023/06/12 21:10:27 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	thinking_state(t_philosopher *philo)
{
	if (philo->is_thinking == 1)
	{
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(&(philo->rules->forks[philo->right_fork]));
			print_state(philo->rules, philo->id, "has taken right fork");
			pthread_mutex_lock(&(philo->rules->forks[philo->left_fork]));
			print_state(philo->rules, philo->id, "has taken left fork");
			philo->is_eating = 1;
			philo->is_thinking = 0;
		}
		else
		{
			pthread_mutex_lock(&(philo->rules->forks[philo->left_fork]));
			print_state(philo->rules, philo->id, "has taken left fork");
			pthread_mutex_lock(&(philo->rules->forks[philo->right_fork]));
			print_state(philo->rules, philo->id, "has taken right fork");
			philo->is_eating = 1;
			philo->is_thinking = 0;
		}
	}
}

void	eating_state(t_philosopher *philo)
{
	if (philo->is_eating == 1)
	{
		pthread_mutex_lock(&(philo->rules->state[philo->id]));
		philo->t_last_meal = ft_timestamp();
		pthread_mutex_unlock(&(philo->rules->state[philo->id]));
		print_state(philo->rules, philo->id, "is eating");
		usleep(philo->rules->t_eat * 1000);
		pthread_mutex_unlock(&(philo->rules->forks[philo->right_fork]));
		print_state(philo->rules, philo->id, "released right fork");
		pthread_mutex_unlock(&(philo->rules->forks[philo->left_fork]));
		print_state(philo->rules, philo->id, "released left fork");
		pthread_mutex_lock(&(philo->rules->state[philo->id]));
		philo->x_ate++;
		pthread_mutex_unlock(&(philo->rules->state[philo->id]));
		philo->is_eating = 0;
		philo->is_sleeping = 1;
	}
}

void	sleeping_state(t_philosopher *philo)
{
	if (philo->is_sleeping)
	{
		print_state(philo->rules, philo->id, "is sleeping");
		usleep(philo->rules->t_sleep * 1000);
		philo->is_sleeping = 0;
		philo->is_thinking = 1;
	}
}
