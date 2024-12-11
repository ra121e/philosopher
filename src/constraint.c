/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constraint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:41:53 by athonda           #+#    #+#             */
/*   Updated: 2024/12/11 15:42:30 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*constraint(void *arg)
{
	long	now;
	long	time;
	int	sec;
	t_philo	*p;

	p = (t_philo *)arg;
	sec = 500000;
	p->start = get_time();
	printf("epoch :%ld ID: %d\n", p->start, p->id);

	now = get_time();
	time = now - p->m->epoch;
	printf("%ld %d is sleeping\n", time, p->id);
	usleep(p->m->time_sleep * 1000);

//	tableware(p);

	now = get_time();
	time = now - p->m->epoch;
	printf("%ld %d is thinking\n", time, p->id);
	usleep(sec);
	return (NULL);
}