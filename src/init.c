/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:01:19 by athonda           #+#    #+#             */
/*   Updated: 2024/12/11 20:52:45 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	init_mutex(t_admin *m)
{
	int	retval;

	retval = pthread_mutex_init(&m->mutex, NULL);
	if (retval != 0)
		return (1);
	return (0);
	// TODO protection
}

void	init_admin(t_admin *m, t_philo *p)
{
	m->epoch = 0;
	m->nb_philo = 0;
	m->time_die = 0;
	m->time_eat = 0;
	m->time_sleep = 0;
	m->dead = 0;
	m->max_eat = 0;
	m->p = p;
}

void	init_philo(t_philo *p, int i, t_admin *m)
{
	p->id = i;
	p->start = 0;
	p->last_supper = 0;
	p->pt = 0;
	p->status = 0;
	p->tv.tv_sec = 0;
	p->tv.tv_usec = 0;
	p->counter = 0;
	p->m = m;
}