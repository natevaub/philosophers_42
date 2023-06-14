
t_philosopher get_philo(t_philosopher *philo, int direction)
{
	printf("Here\n");
	if (direction == 0)
	{
		if (philo->id == 0)
			return (philo[philo->rules->nb_philo - 1]);
		else
			return (philo[philo->id - 1]);
	}
	else if (direction == 1)
	{
		if (philo->id == philo->rules->nb_philo - 1)
			return (philo[0]);
		else
			return (philo[philo->id + 1]);
	}
}

// void	thinking_state(t_philosopher *philo)
// {
// 	if (philo->is_thinking == 1)
// 	{
// 		print_state(philo->rules, philo->id, "is thinking");
// 		if (philo->id % 2 == 0)
// 		{
// 			if (get_philo(philo, 1).t_last_meal < philo->t_last_meal)
// 				return ;
// 			else
// 			{
// 				pthread_mutex_lock(&(philo->rules->forks[philo->right_fork]));
// 				print_state(philo->rules, philo->id, "has taken right fork");
// 				printf("%d Right fork = %d\n", philo->id + 1, philo->right_fork);
// 			}
// 			if (get_philo(philo, 0).t_last_meal < philo->t_last_meal)
// 				return;
// 			else
// 			{
// 				pthread_mutex_lock(&(philo->rules->forks[philo->left_fork]));
// 				print_state(philo->rules, philo->id, "has taken left fork");
// 				printf("%d Left fork = %d\n", philo->id + 1, philo->left_fork);
// 			}
// 			philo->is_eating = 1;
// 			philo->is_thinking = 0;
// 		}
// 		else
// 		{
// 			if (get_philo(philo, 0).t_last_meal < philo->t_last_meal)
// 				return ;
// 			else
// 			{
// 				pthread_mutex_lock(&(philo->rules->forks[philo->left_fork]));
// 				print_state(philo->rules, philo->id, "has taken left fork");
// 				printf("%d Left fork = %d\n", philo->id + 1, philo->left_fork);
// 			}
// 			if (get_philo(philo, 1).t_last_meal < philo->t_last_meal)
// 				return ;
// 			else
// 			{
// 				pthread_mutex_lock(&(philo->rules->forks[philo->right_fork]));
// 				printf("%d Right fork = %d\n", philo->id + 1, philo->right_fork);
// 				print_state(philo->rules, philo->id, "has taken right fork");
// 			}
// 			philo->is_eating = 1;
// 			philo->is_thinking = 0;
// 		}
// 	}
// }