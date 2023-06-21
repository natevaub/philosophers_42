/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:56:02 by nvaubien          #+#    #+#             */
/*   Updated: 2023/06/21 10:48:21 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	mutex_destruction_free(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_mutex_destroy(&(rules->forks[i]));
		pthread_mutex_destroy(&(rules->state[i]));
		i++;
	}
	free(rules->forks);
	free(rules->state);
	pthread_mutex_destroy(&(rules->writing));
	return (0);
}

int	philosopher_free(t_rules *rules)
{
	free(rules->philosopher);
	free(rules);
	return (0);
}

int	clean_philo(t_rules *rules)
{
	mutex_destruction_free(rules);
	philosopher_free(rules);
	return (0);
}
