/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:55:34 by mgarouj           #+#    #+#             */
/*   Updated: 2025/03/21 23:02:54 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
#include <sys/time.h>

typedef struct s_philo
{
	pthread_t		thread_id;        // معرف الخيط المسؤول عن الفيلسوف
	int				philo_id;         // رقم تعريف الفيلسوف
	int				is_eating;        // يشير إلى ما إذا كان الفيلسوف يأكل (1) أو لا (0)
	int				meals_count;      // عدد الوجبات التي أكلها الفيلسوف
	int			last_meal_time;   // توقيت آخر وجبة أكلها الفيلسوف (بالميكروثانية أو الملي ثانية)
	int			simulation_start; // وقت بدء المحاكاة
	int				*is_dead;         // مؤشر إلى متغير يشير إلى ما إذا كان أي فيلسوف قد مات
	pthread_mutex_t	*right_fork;      // مؤشر إلى شوكة الفيلسوف اليمنى (Mutex لحمايتها)
	pthread_mutex_t	*left_fork;       // مؤشر إلى شوكة الفيلسوف اليسرى (Mutex لحمايتها)
	pthread_mutex_t	*output_lock;     // مؤشر إلى Mutex لحماية عمليات الكتابة في المخرجات
	pthread_mutex_t	*death_lock;      // مؤشر إلى Mutex لحماية الوصول إلى حالة الوفاة
	pthread_mutex_t	*meal_lock;       // مؤشر إلى Mutex لحماية وقت آخر وجبة أكلها الفيلسوف
	struct s_table	*table;
}					t_philo;

typedef struct s_table
{
	int				total_philos;     // عدد الفلاسفة في المحاكاة
	int			    death_time;       // المدة الزمنية التي يمكن للفيلسوف البقاء فيها دون طعام قبل أن يموت
	int			    eat_duration;     // المدة الزمنية التي يستغرقها الفيلسوف في الأكل
	int			    sleep_duration;   // المدة الزمنية التي يستغرقها الفيلسوف في النوم
	int				required_meals;   // عدد الوجبات المطلوبة قبل انتهاء المحاكاة
	int				death_status;    // متغير يشير إلى ما إذا كان هناك فيلسوف قد مات (1 = ميت، 0 = لا أحد مات)
	pthread_mutex_t	death_lock;     // Mutex لحماية التعديل على `death_status`
	pthread_mutex_t	meal_lock;      // Mutex لحماية الوصول إلى بيانات الوجبات (مثل `last_meal_time`)
	pthread_mutex_t	output_lock;    // Mutex لحماية عمليات الكتابة على الشاشة (لمنع تداخل المخرجات)
	pthread_mutex_t	*forks;  
	t_philo	        *philo;   // مصفوفة تحتوي على جميع الفلاسفة المشاركين في المحاكاة
}					t_table;

// number_of_philosophers time_to_die time_to_eat time_to_sleep
// [number_of_times_each_philosopher_must_eat]


int	ft_atoi(const char *str);
int	ft_isdigit(char **v);
size_t get_time();
size_t	ft_strlen(const char *s);
void    *monitor(void *arg);
int	 create_thread_philo(t_table *table);
void    ft_print(char *str, t_philo *philo);
int dead(t_philo *philo);
int	ft_usleep(size_t ms);
void	eat(t_philo *philo);
void	thinking(t_philo *philo);
void    sleeping(t_philo *philo);
void des_free_all(char *str, t_table *table);
# endif