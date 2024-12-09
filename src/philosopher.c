/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:07:25 by athonda           #+#    #+#             */
/*   Updated: 2024/12/09 21:18:49 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	err(char *str)
{
	while (*str)
		write(2, str++, 1);
	exit(EXIT_FAILURE);
}

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

long	get_time(void)
{
	struct timeval	tv;
	gettimeofday(&tv, 0);
	return ((long)tv.tv_sec * 1000 + (long)tv.tv_usec / 1000);
}

void	*life(void *arg)
{
	//pthread_t	id;
	long	now;
	long	time;
	int	sec;
	t_philo	*p;

	p = (t_philo *)arg;
	sec = 500000;
//	gettimeofday(&p->tv, NULL);
	now = get_time();
	p->start = now;
	printf("epoch :%ld ID: %d\n", p->start, p->id);

//	gettimeofday(&now, NULL);
	now = get_time();
	time = now - p->start;
	printf("%ld %d: I have woken up\n", time, p->id);
	usleep(sec);
//	time_stamp_s = (int)(now.tv_sec) - (int)(p->tv.tv_sec);
//	time_stamp_m = (int)(now.tv_usec) - (int)(p->tv.tv_usec);

//	tableware(p);

	now = get_time();
	time = now - p->start;
	printf("%ld %d: I am thinking\n", time, p->id);
	usleep(sec);
	return (NULL);
}

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
	int	i;
//	int	ret[NUM_PHILO];
	int	ret;
	int	retval;
	t_philo	p[200];
	t_admin	m;
//	int	epoch;
	//struct timeval tv;
	//pthread_mutex_t	*mutex;
	//pthread_t	pt[NUM_PHILO];
	//struct timezone tz;
	//pthread_t	pt2;

//	p = (t_philo *)malloc(sizeof (t_philo));
//	if (!p)
//		return (0);
//	m = (t_admin *)malloc(sizeof (t_admin));
//	if (!m)
//		return (0);
//	m->mutex = (pthread_mutex_t *)malloc(sizeof (pthread_mutex_t));
//	if (m->mutex == NULL)
//		return (0);
	if (ac < 5 || ac > 6)
	{
		error_exit("wrong argument: 5 800 200 200 [3]\n");
		return (1);
	}
	init_admin(&m);
	set_arg(&m, av);
	retval = pthread_mutex_init(&m.mutex, NULL);
	printf("retval: %d\n", retval);
//	if (retval != 0)
//	{
//		free(m->mutex);
//		return (0);
//	}
	m.epoch = get_time();
	i = 0;
	while (i < NUM_PHILO)
	{
		init_philo(&p[i]);
		p[i].id = i;
		ret = pthread_create(&p[i].pt, NULL, &life, &p[i]);
		usleep(100);
		printf("return value: %d\n", ret);
		printf("thread id: %ld\n", p[i].pt);
		i++;
	}
	sleep(10);
//	retval = pthread_mutex_destroy(m->mutex);
	i = 0;
	while (i < NUM_PHILO)
	{
		pthread_join(p[i].pt, NULL);
		i++;
	}
	return (0);
}