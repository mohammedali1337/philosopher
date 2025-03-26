/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:56:04 by mgarouj           #+#    #+#             */
/*   Updated: 2025/03/26 01:02:05 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
//philo   number_of_philo   time_to_die   time_to_eat   time_to_sleep    num_of_meals
int main(int c, char **v)
{
    t_table table;
    if (c != 5 && c !=6)
    {
        write(2, "Usage: ./philo number_of_philos time_to_die time_to_eat time_to_sleep [must_eat]\n", 82);
        return (1);
    }
    if (init_data(v, &table) != 0)
        return (2);
    if (creat_thread_philo(&table))
        return (3);
}