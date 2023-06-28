/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:21:17 by nvaubien          #+#    #+#             */
/*   Updated: 2023/06/28 11:40:12 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// Philosopher Visualizer : https://nafuka11.github.io/philosophers-visualizer/

int	err_msg(char *s)
{
	int	err;

	err = 1;
	printf("%s", s);
	return (err);
}

int	main(int ac, char **av)
{
	t_rules	*rules;

	rules = NULL;
	rules = malloc(sizeof(t_rules));
	if (init_all(ac, av, rules) != 0)
	{
		printf("Initialization failed\n");
		exit(1);
	}
	philosopher(rules);
	return (0);
}
