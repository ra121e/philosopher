/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:07:25 by athonda           #+#    #+#             */
/*   Updated: 2024/12/11 21:51:47 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"


/*
void	tableware(t_philo *p)
{
	int	retval;
	struct timeval now;
	int	time_stamp_s;
	int	time_stamp_m;
	int	sec;
	int	id;
	int	i;

	i = 0;
//	id = p->num_philo;
	sec = 500000;

	pthread_mutex_lock(m->mutex);
	gettimeofday(&now, NULL);
	time_stamp_s = (int)(now.tv_sec) - (int)(p->tv.tv_sec);
	time_stamp_m = (int)(now.tv_usec) - (int)(p->tv.tv_usec);
	printf("%d:%d %d: I have picked up fork\n", time_stamp_s, time_stamp_m, id);
	printf("%d:%d mutex status: %d\n", time_stamp_s, time_stamp_m, (*p->mutex).__data.__lock);
	printf("%d:%d mutex owner: %d\n", time_stamp_s, time_stamp_m, (*p->mutex).__data.__owner);
	printf("%d:%d mutex waiting num: %d\n", time_stamp_s, time_stamp_m, (*p->mutex).__data.__nusers);
	usleep(sec);
	gettimeofday(&now, NULL);
	time_stamp_s = (int)(now.tv_sec) - (int)(p->tv.tv_sec);
	time_stamp_m = (int)(now.tv_usec) - (int)(p->tv.tv_usec);
	printf("%d:%d %d: I am eating\n", time_stamp_s, time_stamp_m, id);
	usleep(sec);
	gettimeofday(&now, NULL);
	time_stamp_s = (int)(now.tv_sec) - (int)(p->tv.tv_sec);
	time_stamp_m = (int)(now.tv_usec) - (int)(p->tv.tv_usec);
	printf("%d:%d %d: I am enough\n", time_stamp_s, time_stamp_m, id);
	usleep(sec);
	gettimeofday(&now, NULL);
	time_stamp_s = (int)(now.tv_sec) - (int)(p->tv.tv_sec);
	time_stamp_m = (int)(now.tv_usec) - (int)(p->tv.tv_usec);
	printf("%d:%d %d: I have returned forks\n", time_stamp_s, time_stamp_m, id);
	printf("%d:%d counter: %d\n", time_stamp_s, time_stamp_m, p->counter++);
	printf("%d:%d mutex waiting num: %d\n", time_stamp_s, time_stamp_m, (*p->mutex).__data.__nusers);
	pthread_mutex_unlock(m->mutex);
	printf("%d:%d mutex status: %d\n", time_stamp_s, time_stamp_m, (*p->mutex).__data.__lock);
	usleep(sec * 5);

}
*/


void	set_arg(t_admin *m, char **av)
{
	m->nb_philo = ft_atol(av[1]);
	m->time_die = ft_atol(av[2]);
	m->time_eat = ft_atol(av[3]);
	m->time_sleep = ft_atol(av[4]);
	if (av[5])
		m->max_eat = ft_atol(av[5]);
}

int	main(int ac, char **av)
{
	unsigned int	i;
	int	ret;
	t_philo	p[200];
	t_admin	m;

	if (ac < 5 || ac > 6)
	{
		error_exit("wrong argument: ex) 5 800 200 200 [3]\n");
		return (1);
	}
	init_admin(&m, &p[0]);
	if (init_mutex(&m))
		return (0);
	set_arg(&m, av);
	m.start = get_time();
	i = 1;
	while (i <= m.nb_philo)
	{
		init_philo(&p[i], i, &m);
		ret = pthread_create(&p[i].pt, NULL, &constraint, &p[i]);
		if (ret != 0)
			return (0);
		usleep(100);
		i++;
	}
	ret = pthread_create(&m.pt_monitor, NULL, &monitoring, &m);
	if (ret != 0)
		return (0);
	sleep(5);
	pthread_join(m.pt_monitor, NULL);
	i = 0;
	while (i <= m.nb_philo)
	{
		pthread_join(p[i].pt, NULL);
		i++;
	}
	return (0);
}