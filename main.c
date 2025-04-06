/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 12:15:13 by mgarouj           #+#    #+#             */
/*   Updated: 2025/04/06 09:34:24 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int c, char **v)
{
	t_table	table;

	if (c != 5 && c != 6)
		return (1);
	if (!init_table(&table, v))
		return (2);
	if (!init_philo(&table))
		return (3);
	if (!thread_creat(&table))
		return (4);
	free(table.philo);
	return (0);
}
