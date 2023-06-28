/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 20:02:13 by nvaubien          #+#    #+#             */
/*   Updated: 2023/06/28 12:00:06 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define ERR_MALLOC "Error: Failed to allocate memory with malloc\n"
# define ERR_MUTEX "Error: Failed to create mutex\n"
# define ERR_THREAD "Error: Failed to create thread\n"
# define ERR_INVALID_INPUT "Error: Invalid input\n"

typedef struct s_philosopher
{
	int				is_thinking;
	int				is_eating;
	int				is_sleeping;
	int				id;
	int				x_ate;
	int				left_fork;
	int				right_fork;
	long long		t_last_meal;
	struct s_rules	*rules;
	pthread_t		thread_id;
}	t_philosopher;

typedef struct s_rules
{
	int				nb_philo;
	int				t_die;
	int				t_sleep;
	int				t_eat;
	int				nb_eat;
	int				died;
	int				finished;
	long long		first_timestamp;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*state;
	pthread_mutex_t	lock;
	pthread_mutex_t	writing;
	t_philosopher	*philosopher;
}	t_rules;

/* --- checks.c --- */
int				handle_death(t_philosopher *philo, int i);
int				death_check_helper(t_philosopher *philo, int i);
int				death_check(t_philosopher *philo);
void			set_finish_and_unlock(t_philosopher *philo, int i);
int				meal_check(t_philosopher *philo);

/* --- error.c --- */

/* --- init.c --- */
int				check_valid_rules(int ac, char **av);
int				init_mutex(t_rules *rules);
int				init_basic_rules(char **av, t_rules *rules);
int				init_philosopher(t_rules *rules);
int				init_all(int ac, char **av, t_rules *rules);

/* --- main.c --- */
int				err_msg(char *s);

/* --- memory.c --- */
int				mutex_destruction_free(t_rules *rules);
int				philosopher_free(t_rules *rules);
int				clean_philo(t_rules *rules);

/* --- philo.c --- */
int				philosopher(t_rules *rules);
void			*routine(void *arg);

/* --- utils.c --- */
int				ft_philo_atoi(char *s);
long long		ft_timestamp(void);
long long		ft_time_diff(long long past, long long now);
void			print_state(t_rules *rules, int id, char *str);

/* --- state.c --- */
t_philosopher	get_philo(t_philosopher *philo, int direction);
void			thinking_state1(t_philosopher *philo);
void			thinking_state2(t_philosopher *philo);
void			eating_state(t_philosopher *philo);
void			sleeping_state(t_philosopher *philo);

#endif