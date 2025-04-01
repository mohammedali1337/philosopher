#include "philo.h"


/* 
typedef struct s_philo {
	int				nbr;
	uint64_t		last_meal_beginning;
	int				meals_count;
	pthread_t		thread;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
	struct s_args	*args;
}	t_philo;

typedef struct s_args {
	int					philo_count;
	int					time2die;
	int					time2eat;
	int					time2sleep;
	int					max_meals;
	int					total_finished;
	bool				death_occured;
	bool				everybody_full;
	uint64_t			start_time;
	pthread_mutex_t		sync_mutex;
	struct s_philo		philos[200];
}	t_args;
*/

/* 
typedef struct s_philo
{
	pthread_t thread;
	int id_philo;
	size_t last_meals_time;
	int meal_count;
	pthread_mutex_t l_fork;
	pthread_mutex_t *r_fork;
	struct s_table *table;
}	t_philo;

typedef struct s_table
{
	int             num_of_philo;
	int             time_to_die;
	int             time_to_eat;
	int             time_to_sleep;
	int             limit_meals;
	int             philo_fin_eat;
	int             philo_die;
	int             evry_philo_eat;
	size_t          start_time;
	pthread_mutex_t table_mutex;
	t_philo *philo;-
}   t_table;

*/

void f(){system("leaks philo");}

int main(int c, char **v)
{
    t_table table;
    atexit(f);
    
    if (c != 5 && c != 6)
        return (1);
    if (!init_table(&table, v))
        return (2);
    if (!init_philo(&table))
        return (3);
    if (!thread_creat(&table))
        return (4);
    // printf("not this \n");
	free(table.philo);
    return (0);
}