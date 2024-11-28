/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:07:25 by athonda           #+#    #+#             */
/*   Updated: 2024/11/28 17:39:52 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "philosopher.h"
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#define NUM_PHILO 5

typedef struct s_philo
{
	int	num_philo;
	pthread_t	pt[NUM_PHILO];
	struct timeval tv;
	pthread_mutex_t	*mutex;
} t_philo;

void	err(char *str)
{
	write(2, str++, 1);
}

void	tableware(t_philo *p)
{
	int	retval;
	struct timeval now;
	int	time_stamp_s;
	int	time_stamp_m;
	int	sec;
	int	id;

	id = p->num_philo;
	sec = 500000;

	pthread_mutex_lock(p->mutex);
	gettimeofday(&now, NULL);
	time_stamp_s = (int)(now.tv_sec) - (int)(p->tv.tv_sec);
	time_stamp_m = (int)(now.tv_usec) - (int)(p->tv.tv_usec);
	printf("%d:%d %d: I have picked up fork\n", time_stamp_s, time_stamp_m, id);
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
	pthread_mutex_unlock(p->mutex);
	usleep(sec * 5);

}

void	*life(void *arg)
{
	//pthread_t	id;
	int	id;
	struct timeval tv;
	struct timeval now;
	int	time_stamp_s;
	int	time_stamp_m;
	int	sec;
	t_philo	*p;

	p = (t_philo *)arg;
	sec = 500000;
	gettimeofday(&p->tv, NULL);
	printf("epoch :%d %d\n", (int)p->tv.tv_sec, (int)p->tv.tv_usec);
	id = p->num_philo;
//	if (id == 1)
//		usleep(sec * 2);
//	if (id == 2)
//		usleep(sec * 4);
//	if (id == 3)
//		usleep(sec * 6);
//	if (id == 4)
//		usleep(sec * 8);

	gettimeofday(&now, NULL);
	time_stamp_s = (int)(now.tv_sec) - (int)(p->tv.tv_sec);
	time_stamp_m = (int)(now.tv_usec) - (int)(p->tv.tv_usec);
	printf("%d:%d %d: I have woken up\n", time_stamp_s, time_stamp_m, id);
	usleep(sec);
	gettimeofday(&now, NULL);
	time_stamp_s = (int)(now.tv_sec) - (int)(p->tv.tv_sec);
	time_stamp_m = (int)(now.tv_usec) - (int)(p->tv.tv_usec);
	printf("%d:%d %d: I am hungry\n", time_stamp_s, time_stamp_m, id);
	usleep(sec);

	tableware(p);

	gettimeofday(&now, NULL);
	time_stamp_s = (int)(now.tv_sec) - (int)(p->tv.tv_sec);
	time_stamp_m = (int)(now.tv_usec) - (int)(p->tv.tv_usec);
	printf("%d:%d %d: I am thinking\n", time_stamp_s, time_stamp_m, id);
	usleep(sec);
	gettimeofday(&now, NULL);
	time_stamp_s = (int)(now.tv_sec) - (int)(p->tv.tv_sec);
	time_stamp_m = (int)(now.tv_usec) - (int)(p->tv.tv_usec);
	printf("%d:%d %d: I am sleepy\n", time_stamp_s, time_stamp_m, id);
	usleep(sec);
	gettimeofday(&now, NULL);
	time_stamp_s = (int)(now.tv_sec) - (int)(p->tv.tv_sec);
	time_stamp_m = (int)(now.tv_usec) - (int)(p->tv.tv_usec);
	printf("%d:%d %d: zzzz....\n", time_stamp_s, time_stamp_m, id);
	usleep(sec);
	return (NULL);
}

int	main(int ac, char **av)
{
	int	i;
	//pthread_t	pt[NUM_PHILO];
	int	ret[NUM_PHILO];
	//struct timeval tv;
	//pthread_mutex_t	*mutex;
	t_philo	*p;
	//struct timezone tz;
	//pthread_t	pt2;
	int	retval;

	p = (t_philo *)malloc(sizeof (t_philo));
	if (!p)
		return (0);
	p->mutex = (pthread_mutex_t *)malloc(sizeof (pthread_mutex_t));
	if (p->mutex == NULL)
		return (0);
	retval = pthread_mutex_init(p->mutex, NULL);
	if (retval != 0)
	{
		free(p->mutex);
		return (0);
	}
	gettimeofday(&p->tv, NULL);
	printf("epoch :%d %d\n", (int)p->tv.tv_sec, (int)p->tv.tv_usec);
	i = 0;
	while (i < NUM_PHILO)
	{
		p->num_philo = i;
		ret[i] = pthread_create(&p->pt[i], NULL, &life, (void *)p);
		printf("return value: %d\n", ret[i]);
		printf("thread id: %ld\n", p->pt[i]);
		i++;
	}
	sleep(10);
	retval = pthread_mutex_destroy(p->mutex);
	//i = pthread_create(&pt2, NULL, &life, (void *)pt2);
	//printf("return value: %d\n", i);
	//printf("thread id: %ld\n", pt2);
	i = 0;
	while (i < NUM_PHILO)
	{
		pthread_join(p->pt[i], NULL);
		i++;
	}
	//pthread_join(pt2, NULL);
	return (0);
}