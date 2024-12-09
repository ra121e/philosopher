/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:01:19 by athonda           #+#    #+#             */
/*   Updated: 2024/12/09 21:18:43 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	init_admin(t_admin *m)
{
	m->epoch = 0;
	m->nb_philo = 0;
	m->time_die = 0;
	m->time_eat = 0;
	m->time_sleep = 0;
	m->dead = 0;
	m->max_eat = 0;
	m->p = 0;
}

void	init_philo(t_philo *p)
{
	p->id = 0;
	p->start = 0;
	p->pt = 0;
	p->tv.tv_sec = 0;
	p->tv.tv_usec = 0;
	p->counter = 0;
}