/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:56:02 by nvaubien          #+#    #+#             */
/*   Updated: 2023/06/19 21:52:52 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// int	mutex_destruction_free(t_rules *rules)
// {
// 	printf("In mutex Destruction\n");
// 	int	i;

// 	i = 0;
// 	while (i < rules->nb_philo)
// 	{
// 		pthread_mutex_destroy(&(rules->forks[i]));
// 		pthread_mutex_destroy(&(rules->state[i]));
// 	}
	// free(rules->forks);
	// free(rules->state);
	// pthread_mutex_destroy(&(rules->writing));
// 	return (0);
// }

// int	thread_exit_free(t_rules *rules)
// {
// 	int	i;

// 	i = 0;
// 	while (i < rules->nb_philo)
// 	{
// 		pthread_cancel(&(rules->philosopher[i].thread_id));
// 		i++;
// 	}
// 	return (0);
// }

// int	clean_philo(t_rules *rules)
// {
// 	mutex_destruction_free(rules);
// 	thread_exit_free(rules);
// 	return (0);
// }
