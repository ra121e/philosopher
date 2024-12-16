/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   friction.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 20:30:19 by athonda           #+#    #+#             */
/*   Updated: 2024/12/16 15:41:49 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	taking_left(t_philo *p)
{
	long	now;
	long	time;

	p->m->used[p->id - 1] = 1;
	pthread_mutex_lock(&p->m->mutex_print);
	now = get_time();
	time = now - p->m->start;
	printf("%ld %d has taken a fork\n", time, p->id);
	pthread_mutex_unlock(&p->m->mutex_print);
}

void	taking_right(t_philo *p)
{
	long	now;
	long	time;

	p->m->used[p->id % p->m->nb_philo] = 1;
	pthread_mutex_lock(&p->m->mutex_print);
	now = get_time();
	time = now - p->m->start;
	printf("%ld %d has taken a fork\n", time, p->id);
	pthread_mutex_unlock(&p->m->mutex_print);
}

void	eating(t_philo *p)
{
	long	now;
	long	time;

	pthread_mutex_lock(&p->m->mutex_print);
	now = get_time();
	time = now - p->m->start;
	printf("%ld %d is eating\n", time, p->id);
	pthread_mutex_unlock(&p->m->mutex_print);
	p->last_supper = now;
	p->status = EATING;
	p->counter++;
	usleep(p->m->time_eat * 1000);
	if (p->m->max_eat > 0 && p->counter >= p->m->max_eat)
		p->full = 1;
}

void	thinking(t_philo *p)
{
	long	now;
	long	time;

	pthread_mutex_lock(&p->m->mutex_print);
	now = get_time();
	time = now - p->m->start;
	printf("%ld %d is thinking\n", time, p->id);
	pthread_mutex_unlock(&p->m->mutex_print);
	p->status = THINKING;
	if (p->id % 2 == 0)
		usleep(7000);
}

void	sleeping(t_philo *p)
{
	long	now;
	long	time;

	pthread_mutex_lock(&p->m->mutex_print);
	now = get_time();
	time = now - p->m->start;
	printf("%ld %d is sleeping\n", time, p->id);
	pthread_mutex_unlock(&p->m->mutex_print);
	p->status = SLEEPING;
	usleep(p->m->time_sleep * 1000);
}
