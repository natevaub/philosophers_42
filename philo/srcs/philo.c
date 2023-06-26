/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:48:18 by nvaubien          #+#    #+#             */
/*   Updated: 2023/06/27 00:41:32 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int philosopher(t_rules *rules)
{
	int i;
	int res;

	i = 0;
	while (i < rules->nb_philo)
	{
		res = pthread_create(&(rules->philosopher[i].thread_id),
							 NULL, &routine, &(rules->philosopher[i]));
		if (res != 0)
			return (1);
		i++;
	}
	while (1)
	{
		// printf("In while\n");
		if (meal_check(rules->philosopher) == 1 || death_check(rules->philosopher) == 1)
		{
			break;
		}
			
		usleep(500);
	}
	printf("KSDJNFSDJKN \n");
	// What ???
	i = 0;
	while (i < rules->nb_philo)
	{
		printf("CHOTO MATA \n");
		pthread_join(rules->philosopher[i].thread_id, NULL);
		i++;
	}
	printf("After\n");
	clean_philo(rules);
	return (0);
}

void *routine(void *arg)
{
	t_philosopher *philo;

	philo = (t_philosopher *)arg;
	print_state(philo->rules, philo->id, "is thinking");
	
	while (1)
	{
		printf("JDAD %d \n", philo->id + 1);
		pthread_mutex_lock(&(philo->rules->lock));
		if (philo->rules->finished == 1)
		{
			pthread_mutex_unlock(&(philo->rules->lock));
			// usleep(100);
			printf("Here %d \n", philo->id + 1);
			break;
		}
		pthread_mutex_unlock(&(philo->rules->lock));
		printf("JDOOOODD %d \n", philo->id + 1);
		if (philo->is_thinking == 1) {
			printf("JDOOOODD PIOTR %d \n", philo->id + 1);
			thinking_state1(philo);
		}
		printf("JDOOOODD LAND %d \n", philo->id + 1);
		if (philo->is_eating == 1) {
			eating_state(philo);
		}
		printf("JDOOOODD ISLAND %d \n", philo->id + 1);
		if (philo->is_sleeping == 1) {
			sleeping_state(philo);
		}
	}
	return (NULL);
}
