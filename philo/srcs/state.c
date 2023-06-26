/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:11:44 by nvaubien          #+#    #+#             */
/*   Updated: 2023/06/27 00:38:57 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philosopher	get_philo(t_philosopher *philo, int direction)
{
    pthread_mutex_lock(&(philo->rules->lock));
	int	j;
	int	n_philo;

	j = philo->id;
	n_philo = philo->rules->nb_philo;
	if (direction)
		j += 1;
	else
		j -= 1;
	if (j < 0)
    {
        
        t_philosopher a = philo->rules->philosopher[n_philo - 1];
        pthread_mutex_unlock(&(philo->rules->lock));
		return (a);
    }
	else
    {
        t_philosopher a = philo->rules->philosopher[j % n_philo];
        pthread_mutex_unlock(&(philo->rules->lock));
		return (a);
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
    printf("RIPU \n");
}

void	thinking_state2(t_philosopher *philo)
{
    printf("MOTO \n");
	if (philo->is_thinking == 1 && philo->id % 2 != 0)
	{
        printf("1 MOTOO %d \n", philo->id + 1);
		while (get_philo(philo, 0).t_last_meal < philo->t_last_meal)
		{
		}
        printf("2 MOTOO %d \n", philo->id + 1);
		pthread_mutex_lock(&(philo->rules->forks[philo->left_fork]));
        printf("3 MOTOO %d \n", philo->id + 1);
		print_state(philo->rules, philo->id, "has taken a fork");
		while (get_philo(philo, 1).t_last_meal < philo->t_last_meal)
		{
		}
        printf("4 MOTOO %d \n", philo->id + 1);
		pthread_mutex_lock(&(philo->rules->forks[philo->right_fork]));
        printf("5 MOTOO %d \n", philo->id + 1);
		print_state(philo->rules, philo->id, "has taken a fork");
        printf("6 MOTOO %d \n", philo->id + 1);
	}
    // pthread_mutex_lock(&(philo->rules->lock));
	// philo->is_eating = 1;
	// philo->is_thinking = 0;
    // pthread_mutex_unlock(&(philo->rules->lock));
}

void	eating_state(t_philosopher *philo)
{
	if (philo->is_eating == 1)
	{
		// pthread_mutex_lock(&(philo->rules->state[philo->id]));
		pthread_mutex_lock(&(philo->rules->lock));
		philo->t_last_meal = ft_timestamp();
		// pthread_mutex_unlock(&(philo->rules->state[philo->id]));
		pthread_mutex_unlock(&(philo->rules->lock));
		print_state(philo->rules, philo->id, "is eating");
		usleep(philo->rules->t_eat * 1000);
		pthread_mutex_unlock(&(philo->rules->forks[philo->right_fork]));
		pthread_mutex_unlock(&(philo->rules->forks[philo->left_fork]));
		// pthread_mutex_lock(&(philo->rules->state[philo->id]));
		pthread_mutex_lock(&(philo->rules->lock));
		philo->x_ate++;
		philo->is_eating = 0;
		philo->is_sleeping = 1;
		pthread_mutex_unlock(&(philo->rules->lock));
		// pthread_mutex_unlock(&(philo->rules->state[philo->id]));
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
