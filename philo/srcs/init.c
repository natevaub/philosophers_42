/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:18:42 by nvaubien          #+#    #+#             */
/*   Updated: 2023/06/25 22:36:24 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_valid_rules(int ac, char **av, t_rules *rules)
{
	if (ac < 5 || ac > 6)
		return (1);
	if (ft_philo_atoi(av[1]) < 1 || ft_philo_atoi(av[2]) < 0
		|| ft_philo_atoi(av[3]) < 0 || ft_philo_atoi(av[4]) < 0)
		return (1);
	return (0);
}

int	init_mutex(t_rules *rules)
{
	int	i;

	i = 0;
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->nb_philo);
	rules->state = malloc(sizeof(pthread_mutex_t) * rules->nb_philo);
	while (i < rules->nb_philo)
	{
		if (pthread_mutex_init(&(rules->forks[i]), NULL) != 0)
			return (1);
		if (pthread_mutex_init(&(rules->state[i]), NULL) != 0)
			return (1);
		i++;
	}
    if (pthread_mutex_init(&(rules->lock), NULL) != 0)
	if (pthread_mutex_init(&(rules->writing), NULL) != 0)
		return (1);
	return (0);
}

int	init_basic_rules(char **av, t_rules *rules)
{
	rules->nb_philo = ft_philo_atoi(av[1]);
	rules->t_die = ft_philo_atoi(av[2]);
	rules->t_eat = ft_philo_atoi(av[3]);
	rules->t_sleep = ft_philo_atoi(av[4]);
	rules->nb_eat = -1;
    pthread_mutex_init(&rules->writing, NULL);
	return (0);
}

int	init_philosopher(t_rules *rules)
{
	int	i;

	i = 0;
	rules->philosopher = malloc(sizeof(t_philosopher) * rules->nb_philo);
	while (i < rules->nb_philo)
	{
		rules->philosopher[i].is_thinking = 1;
		rules->philosopher[i].is_eating = 0;
		rules->philosopher[i].is_sleeping = 0;
		rules->philosopher[i].id = i;
		rules->philosopher[i].x_ate = 0;
		rules->philosopher[i].left_fork = i;
		rules->philosopher[i].right_fork = (i + 1) % rules->nb_philo;
		rules->philosopher[i].t_last_meal = -1;
		rules->philosopher[i].rules = rules;
		i++;
	}
	return (0);
}

int	init_all(int ac, char **av, t_rules *rules)
{
	if (check_valid_rules(ac, av, rules) != 0)
		return (1);
	init_basic_rules(av, rules);
	rules->first_timestamp = ft_timestamp();
	rules->died = 0;
	rules->finished = 0;
	if (init_mutex(rules) != 0)
		return (1);
	if (av[5])
	{
		rules->nb_eat = ft_philo_atoi(av[5]);
		if (rules->nb_eat <= 0)
			return (1);
	}
	else
		rules->nb_eat = -1;
	if (init_philosopher(rules) != 0)
		return (1);
	return (0);
}
