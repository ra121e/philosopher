/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   friction_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 20:30:19 by athonda           #+#    #+#             */
/*   Updated: 2025/01/01 09:44:04 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

int	taking(t_admin *m, t_philo *p)
{
	long	now;
	long	time;

	sem_wait(m->sem_print);
	now = get_time();
	time = now - m->start;
	printf("%ld %d has taken a fork\n", time, p->id);
	sem_post(m->sem_print);
	return (ALIVE);
}

int	eating(t_admin *m, t_philo *p)
{
	long	now;
	long	time;

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
	p->status = EATING;
	p->counter++;
	sem_post(m->sem_count);
	usleep(m->time_eat * 1000);
	sem_post(m->stick);
	sem_post(m->stick);
	if (m->max_eat > 0 && p->counter >= m->max_eat)
	{
		p->full = 1;
		return (1);
	}
	return (0);
}

int	thinking(t_admin *m, t_philo *p)
{
	long	now;
	long	time;

	if (p->status == THINKING)
		return (0);
	sem_wait(m->sem_print);
	now = get_time();
	time = now - m->start;
	printf("%ld %d is thinking\n", time, p->id);
	sem_post(m->sem_print);
	p->status = THINKING;
	if (m->time_eat > m->time_sleep)
		usleep(m->time_eat - m->time_sleep + 1000);
	else
		usleep(1000);
	return (0);
}

int	sleeping(t_admin *m, t_philo *p)
{
	long	now;
	long	time;

	if (p->status != EATING || p->full == 1)
		exit(0);
	sem_wait(m->sem_print);
	now = get_time();
	time = now - m->start;
	printf("%ld %d is sleeping\n", time, p->id);
	sem_post(m->sem_print);
	p->status = SLEEPING;
	usleep(m->time_sleep * 1000);
	return (ALIVE);
}
