#include "../includes/philo.h"

int	main(int ac, char **av)
{
	t_rules *rules				= NULL;
	rules = malloc(sizeof(t_rules));
	if (init_all(ac, av, rules) != 0)
	{
		printf("Initialization failed\n");
		exit(1);
	}
		
	// printf("|---	Nb of philo	=	%d		---|\n", rules->nb_philo);
	// printf("|---	t_die		=	%d		---|\n", rules->t_die);
	// printf("|---	t_sleep		=	%d		---|\n", rules->t_die);
	// printf("|---	t_eat		=	%d		---|\n", rules->t_eat);
	// printf("|---	nb_eat		=	%d		---|\n", rules->nb_eat);
	// printf("|---	first		=	%lld	---|\n", rules->first_timestamp);
	// for (int i = 0; i < rules->nb_philo; i++)
	// {
	// 	printf("----------------------------------------------------\n");
	// 	printf("|---	Philo id	=	%d		---|\n", rules->philosopher[i].id);
	// 	printf("|---	x ate		=	%d		---|\n", rules->philosopher[i].x_ate);
	// 	printf("|---	left fork	=	%d		---|\n", rules->philosopher[i].left_fork);
	// 	printf("|---	right fork	=	%d		---|\n", rules->philosopher[i].right_fork);
	// 	printf("|---	t_lmeal		=	%lld		---|\n", rules->philosopher[i].t_last_meal);
	// }
	philosopher(rules);
	return (0);

}