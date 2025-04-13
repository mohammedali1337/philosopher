# include <stdio.h>
# include <limits.h>
# include <string.h> 
# include <stdint.h> 
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <semaphore.h>

typedef struct s_philo
{
	pid_t   		pid;
	int				id_philo;
	size_t			last_meals_time;
	int				meal_count;
	sem_t       	l_fork;
	sem_t       	*r_fork;
	struct s_table	*table;
}					t_philo;

typedef struct s_table
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				limit_meals;
	int				philo_fin_eat;
	int				philo_die;
	int				evry_philo_eat;
	size_t			start_time;
	sem_t       	table_mutex;
	t_philo			*philo;
}					t_table;