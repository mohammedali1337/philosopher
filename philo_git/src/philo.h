/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:20:06 by druina            #+#    #+#             */
/*   Updated: 2025/03/21 05:00:00 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define PHILO_MAX 300

typedef struct s_philo
{
	pthread_t		thread;          // معرف (ID) الخيط المسؤول عن الفيلسوف
	int				id;              // رقم تعريف الفيلسوف
	int				eating;          // متغير يشير إلى ما إذا كان الفيلسوف يأكل (1) أو لا (0)
	int				meals_eaten;     // عدد الوجبات التي أكلها الفيلسوف
	size_t			last_meal;       // توقيت آخر وجبة أكلها الفيلسوف (بالميكروثانية أو الملي ثانية)
	size_t			time_to_die;     // الزمن الذي يستطيع الفيلسوف البقاء حيًا بعد آخر وجبة قبل أن يموت
	size_t			time_to_eat;     // المدة الزمنية التي يستغرقها الفيلسوف في الأكل
	size_t			time_to_sleep;   // المدة الزمنية التي يستغرقها الفيلسوف في النوم
	size_t			start_time;      // وقت بدء المحاكاة
	int				num_of_philos;   // عدد الفلاسفة في المحاكاة
	int				num_times_to_eat;// عدد المرات التي يجب على الفيلسوف أن يأكلها قبل انتهاء المحاكاة
	int				*dead;           // مؤشر إلى متغير يشير إلى ما إذا كان أي فيلسوف قد مات
	pthread_mutex_t	*r_fork;         // مؤشر إلى شوكة الفيلسوف اليمنى (Mutex لحمايتها)
	pthread_mutex_t	*l_fork;         // مؤشر إلى شوكة الفيلسوف اليسرى (Mutex لحمايتها)
	pthread_mutex_t	*write_lock;     // مؤشر إلى Mutex لحماية عمليات الكتابة في المخرجات
	pthread_mutex_t	*dead_lock;      // مؤشر إلى Mutex لحماية الوصول إلى حالة الوفاة
	pthread_mutex_t	*meal_lock;      // مؤشر إلى Mutex لحماية وقت آخر وجبة أكلها الفيلسوف
}					t_philo;

typedef struct s_program
{
	int				dead_flag;      // متغير يشير إلى ما إذا كان هناك فيلسوف قد مات (1 = ميت، 0 = لا أحد مات)
	pthread_mutex_t	dead_lock;      // Mutex لحماية التعديل على `dead_flag`
	pthread_mutex_t	meal_lock;      // Mutex لحماية الوصول إلى بيانات الوجبات (مثل `last_meal`)
	pthread_mutex_t	write_lock;     // Mutex لحماية عمليات الكتابة على الشاشة (لمنع تداخل المخرجات)
	t_philo			*philos;        // مصفوفة تحتوي على جميع الفلاسفة المشاركين في المحاكاة
}					t_program;


// Main functions
int					check_arg_content(char *arg);
int					check_valid_args(char **argv);
void				destory_all(char *str, t_program *program,
						pthread_mutex_t *forks);

// Initialization
void				init_program(t_program *program, t_philo *philos);
void				init_forks(pthread_mutex_t *forks, int philo_num);
void				init_philos(t_philo *philos, t_program *program,
						pthread_mutex_t *forks, char **argv);
void				init_input(t_philo *philo, char **argv);

// Threads
int					thread_create(t_program *program, pthread_mutex_t *forks);
void				*monitor(void *pointer);
void				*philo_routine(void *pointer);

// Actions
void				eat(t_philo *philo);
void				dream(t_philo *philo);
void				think(t_philo *philo);

// Monitor utils
int					dead_loop(t_philo *philo);
int					check_if_all_ate(t_philo *philos);
int					check_if_dead(t_philo *philos);
int					philosopher_dead(t_philo *philo, size_t time_to_die);

// Utils
int					ft_atoi(char *str);
int					ft_usleep(size_t microseconds);
int					ft_strlen(char *str);
void				print_message(char *str, t_philo *philo, int id);
size_t				get_current_time(void);

#endif
