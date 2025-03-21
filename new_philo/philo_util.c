#include "philo.h"

size_t get_time()
{
	struct timeval  time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "error in gettimeofday()\n", 25);
	return(time.tv_sec * 1000 + time.tv_usec / 1000);
}

int dead(t_philo *philo)
{
	pthread_mutex_lock(philo->death_lock);
	if (*philo->is_dead == 1)
		return (pthread_mutex_unlock(philo->death_lock), 1);
	pthread_mutex_unlock(philo->death_lock);
	return (0);
}

int	ft_usleep(size_t ms)
{
	size_t start;

	start = get_time();
	while ((get_time() - start) < ms)
		usleep(500);
	return (0);
}

void    *routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2 == 0)
		ft_usleep(1);
	while (!dead(philo))
	{
		eat(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (arg);
}

int create_thread_philo(t_table *table)
{
	pthread_t   observer;
	int         i;

	if (pthread_create(&observer, NULL, &monitor, table))
		des_free_all("thead creation error\n", table);
	i = 0;
	while (i < table->total_philos)
	{
		if (pthread_create(&table->philo[i].thread_id, NULL, &routine, &table->philo[i]) != 0)
			des_free_all("thread creation error\n", table);
		i++;
	}
	i = 0;
	printf("note this \n");
	if (pthread_join(observer, NULL) != 0)
		des_free_all("thread join error\n", table);
	while ( i < table->total_philos)
	{
		if (pthread_join(table->philo[i].thread_id, NULL) != 0)
			des_free_all("thread join error\n", table);
		i++;
	}
	return (0);
}