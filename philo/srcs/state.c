/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:11:44 by nvaubien          #+#    #+#             */
/*   Updated: 2023/06/19 21:18:41 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philosopher	get_philo(t_philosopher *philo, int direction)
{
	int	j;
	int	n_philo;

	j = philo->id;
	n_philo = philo->rules->nb_philo;
	if (direction)
		j += 1;
	else
		j -= 1;
	if (j < 0)
		return (philo->rules->philosopher[n_philo - 1]);
	else
		return (philo->rules->philosopher[j % n_philo]);
}

void	thinking_state(t_philosopher *philo)
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
			philo->is_eating = 1;
			philo->is_thinking = 0;
		}
		else
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
			philo->is_eating = 1;
			philo->is_thinking = 0;
		}
	}
}

void	eating_state(t_philosopher *philo)
{
	if (philo->is_eating == 1)
	{
		if (philo->rules->finished == 1)
		{
			// printf("YOKOKO\n");
			pthread_mutex_unlock(&(philo->rules->forks[philo->left_fork]));
			pthread_mutex_unlock(&(philo->rules->forks[philo->right_fork]));
			// printf("YOKOKI\n");
		}
		printf("ICI\n");
		pthread_mutex_lock(&(philo->rules->state[philo->id]));
		philo->t_last_meal = ft_timestamp();
		pthread_mutex_unlock(&(philo->rules->state[philo->id]));
		print_state(philo->rules, philo->id, "is eating");
		usleep(philo->rules->t_eat * 1000);
		pthread_mutex_unlock(&(philo->rules->forks[philo->right_fork]));
		pthread_mutex_unlock(&(philo->rules->forks[philo->left_fork]));
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
		print_state(philo->rules, philo->id, "is thinking");
	}
}
