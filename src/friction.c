/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   friction.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 20:30:19 by athonda           #+#    #+#             */
/*   Updated: 2025/01/01 17:55:35 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	taking_left(t_philo *p)
{
	long	now;
	long	time;

	p->m->used[p->id - 1] = 1;
	pthread_mutex_lock(&p->m->mutex_print);
	{
		if (checking(p) == DEAD)
			return (pthread_mutex_unlock(&p->m->mutex_print), DEAD);
		now = get_time();
		time = now - p->m->start;
		printf("%ld %d has taken a fork\n", time, p->id);
	}
	pthread_mutex_unlock(&p->m->mutex_print);
	return (0);
}

int	taking_right(t_philo *p)
{
	long	now;
	long	time;

	p->m->used[p->id % p->m->nb_philo] = 1;
	pthread_mutex_lock(&p->m->mutex_print);
	{
		if (checking(p) == DEAD)
			return (pthread_mutex_unlock(&p->m->mutex_print), DEAD);
		now = get_time();
		time = now - p->m->start;
		printf("%ld %d has taken a fork\n", time, p->id);
	}
	pthread_mutex_unlock(&p->m->mutex_print);
	return (ALIVE);
}

int	eating(t_philo *p)
{
	long	now;
	long	time;

	pthread_mutex_lock(&p->m->mutex_print);
	{
		if (checking(p) == DEAD)
			return (pthread_mutex_unlock(&p->m->mutex_print), DEAD);
		now = get_time();
		pthread_mutex_lock(&p->m->mutex_time);
		time = now - p->m->start;
		pthread_mutex_unlock(&p->m->mutex_time);
		p->last_supper = now;
		printf("%ld %d is eating\n", time, p->id);
	}
	pthread_mutex_unlock(&p->m->mutex_print);
	p->status = EATING;
	p->counter++;
	usleep(p->m->time_eat * 1000);
	if (p->m->max_eat > 0 && p->counter >= p->m->max_eat)
		p->full = 1;
	return (0);
}

int	thinking(t_philo *p)
{
	long	now;
	long	time;

	if (p->status == THINKING)
		return (0);
	pthread_mutex_lock(&p->m->mutex_print);
	{
		if (checking(p) == DEAD)
			return (pthread_mutex_unlock(&p->m->mutex_print), DEAD);
		now = get_time();
		time = now - p->m->start;
		printf("%ld %d is thinking\n", time, p->id);
	}
	pthread_mutex_unlock(&p->m->mutex_print);
	p->status = THINKING;
	if (p->m->time_eat > p->m->time_sleep)
		usleep((p->m->time_eat - p->m->time_sleep) * 1000 + 1000);
	else
		usleep(1000);
	return (0);
}

int	sleeping(t_philo *p)
{
	long	now;
	long	time;

	if (p->status != EATING || p->full == 1)
		return (0);
	pthread_mutex_lock(&p->m->mutex_print);
	{
		if (checking(p) == DEAD)
			return (pthread_mutex_unlock(&p->m->mutex_print), DEAD);
		now = get_time();
		time = now - p->m->start;
		printf("%ld %d is sleeping\n", time, p->id);
	}
	pthread_mutex_unlock(&p->m->mutex_print);
	p->status = SLEEPING;
	usleep(p->m->time_sleep * 1000);
	return (ALIVE);
}
