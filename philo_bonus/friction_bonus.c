/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   friction_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 20:30:19 by athonda           #+#    #+#             */
/*   Updated: 2024/12/31 14:03:22 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"
/*
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
*/

int	taking(t_admin *m, t_philo *p)
{
	long	now;
	long	time;

//	pthread_mutex_lock(&p->m->mutex_print);
//	{
//		if (checking(p) == DEAD)
//			return (pthread_mutex_unlock(&p->m->mutex_print), DEAD);
	sem_wait(m->sem_print);
	now = get_time();
	time = now - m->start;
	printf("%ld %d has taken a fork\n", time, p->id);
	sem_post(m->sem_print);
//	}
//	pthread_mutex_unlock(&p->m->mutex_print);
	return (ALIVE);
}


int	eating(t_admin *m, t_philo *p)
{
	long	now;
	long	time;

//	pthread_mutex_lock(&p->m->mutex_print);
//	{
//		if (checking(p) == DEAD)
//			return (pthread_mutex_unlock(&p->m->mutex_print), DEAD);
	sem_wait(m->stick);
	taking(m, p);
	sem_wait(m->stick);
	taking(m, p);
	sem_wait(m->sem_print);
	now = get_time();
	time = now - m->start;
	p->last_supper = now;
	printf("%ld %d is eating\n", time, p->id);
	sem_post(m->sem_print);
//	}
//	pthread_mutex_unlock(&p->m->mutex_print);
	p->status = EATING;
	p->counter++;
	usleep(m->time_eat * 1000);
	sem_post(m->stick);
	sem_post(m->stick);
	if (m->max_eat > 0 && p->counter >= m->max_eat)
		p->full = 1;
	return (0);
}

int	thinking(t_admin *m, t_philo *p)
{
	long	now;
	long	time;

	if (p->status == THINKING)
		return (0);
//		if (checking(p) == DEAD)
//			return (pthread_mutex_unlock(&p->m->mutex_print), DEAD);
	sem_wait(m->sem_print);
	now = get_time();
	time = now - m->start;
	printf("%ld %d is thinking\n", time, p->id);
	sem_post(m->sem_print);
	p->status = THINKING;
//	if (p->m->time_eat > p->m->time_sleep)
//		usleep(p->m->time_eat - p->m->time_sleep + 1000);
//	else
	usleep(1000);
	return (0);
}

int	sleeping(t_admin *m, t_philo *p)
{
	long	now;
	long	time;

//	if (p->status != EATING || p->full == 1)
//		return (0);
//	pthread_mutex_lock(&p->m->mutex_print);
//	{
//		if (checking(p) == DEAD)
//			return (pthread_mutex_unlock(&p->m->mutex_print), DEAD);
	sem_wait(m->sem_print);
	now = get_time();
	time = now - m->start;
	printf("%ld %d is sleeping\n", time, p->id);
	sem_post(m->sem_print);
//	}
//	pthread_mutex_unlock(&p->m->mutex_print);
	p->status = SLEEPING;
	usleep(m->time_sleep * 1000);
	return (ALIVE);
}
