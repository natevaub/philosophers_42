/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:48:18 by nvaubien          #+#    #+#             */
/*   Updated: 2023/06/27 15:53:22 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	philosopher(t_rules *rules)
{
	int	i;
	int	res;

	i = 0;
	while (i < rules->nb_philo)
	{
		res = pthread_create(&(rules->philosopher[i].thread_id),
				NULL, &routine, &(rules->philosopher[i]));
		if (res != 0)
			return (err_msg(ERR_THREAD));
		i++;
	}
	while (1)
	{
		if (meal_check(rules->philosopher) == 1
			|| death_check(rules->philosopher) == 1)
			break ;
		usleep(100);
	}
	i = -1;
	while (++i < rules->nb_philo)
		pthread_join(rules->philosopher[i].thread_id, NULL);
	clean_philo(rules);
	return (0);
}

void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	print_state(philo->rules, philo->id, "is thinking");
	while (1)
	{
		pthread_mutex_lock(&(philo->rules->lock));
		if (philo->rules->finished == 1)
		{
			pthread_mutex_unlock(&(philo->rules->lock));
			// usleep(1);
			break ;
		}
		pthread_mutex_unlock(&(philo->rules->lock));
		if (philo->is_thinking == 1)
			thinking_state1(philo);
		if (philo->is_eating == 1)
			eating_state(philo);
		if (philo->is_sleeping == 1)
			sleeping_state(philo);
	}
	return (NULL);
}
