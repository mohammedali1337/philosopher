/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 23:46:34 by mgarouj           #+#    #+#             */
/*   Updated: 2025/03/12 23:49:17 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int c, char **v)
{
	t_table table;
	if (c != 5 && c != 6)
		return (printf("Usage: ./philo number_of_philos time_to_die time_to_eat time_to_sleep [must_eat]\n"), 1);
	if (!valide_input(v, &table))
		return (printf("invalide input \n"), 1);
	init_philo(&table);
	start_simulation(&table);
	init_fork(&table);
}