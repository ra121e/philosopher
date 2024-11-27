/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:07:25 by athonda           #+#    #+#             */
/*   Updated: 2024/11/27 13:39:18 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "philosopher.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#define NUM_PHILO 5

void	*life(void *arg)
{
	//pthread_t	id;
	int	id;
	struct timeval tv;
	struct timeval now;
	int	time_stamp_s;
	int	time_stamp_m;

	//id = (pthread_t)arg;
	gettimeofday(&tv, NULL);
	printf("epoch :%d %d\n", (int)tv.tv_sec, (int)tv.tv_usec);
	id = *(int *)arg;
	if (id == 1)
		sleep(1);
	if (id == 2)
		sleep(2);
	if (id == 3)
		sleep(3);
	if (id == 4)
		sleep(4);

	gettimeofday(&now, NULL);
	time_stamp_s = (int)(now.tv_sec) - (int)(tv.tv_sec);
	time_stamp_m = (int)(now.tv_usec) - (int)(tv.tv_usec);
	printf("%d:%d %d: I have woken up\n", time_stamp_s, time_stamp_m, id);
	sleep(1);
	gettimeofday(&now, NULL);
	time_stamp_s = (int)(now.tv_sec) - (int)(tv.tv_sec);
	time_stamp_m = (int)(now.tv_usec) - (int)(tv.tv_usec);
	printf("%d:%d %d: I am hungry\n", time_stamp_s, time_stamp_m, id);
	sleep(1);
	gettimeofday(&now, NULL);
	time_stamp_s = (int)(now.tv_sec) - (int)(tv.tv_sec);
	time_stamp_m = (int)(now.tv_usec) - (int)(tv.tv_usec);
	printf("%d:%d %d: I have picked up fork\n", time_stamp_s, time_stamp_m, id);
	sleep(1);
	gettimeofday(&now, NULL);
	time_stamp_s = (int)(now.tv_sec) - (int)(tv.tv_sec);
	time_stamp_m = (int)(now.tv_usec) - (int)(tv.tv_usec);
	printf("%d:%d %d: I am eating\n", time_stamp_s, time_stamp_m, id);
	sleep(1);
	gettimeofday(&now, NULL);
	time_stamp_s = (int)(now.tv_sec) - (int)(tv.tv_sec);
	time_stamp_m = (int)(now.tv_usec) - (int)(tv.tv_usec);
	printf("%d:%d %d: I am enough\n", time_stamp_s, time_stamp_m, id);
	sleep(1);
	gettimeofday(&now, NULL);
	time_stamp_s = (int)(now.tv_sec) - (int)(tv.tv_sec);
	time_stamp_m = (int)(now.tv_usec) - (int)(tv.tv_usec);
	printf("%d:%d %d: I have returned forks\n", time_stamp_s, time_stamp_m, id);
	sleep(1);
	gettimeofday(&now, NULL);
	time_stamp_s = (int)(now.tv_sec) - (int)(tv.tv_sec);
	time_stamp_m = (int)(now.tv_usec) - (int)(tv.tv_usec);
	printf("%d:%d %d: I am thinking\n", time_stamp_s, time_stamp_m, id);
	sleep(1);
	gettimeofday(&now, NULL);
	time_stamp_s = (int)(now.tv_sec) - (int)(tv.tv_sec);
	time_stamp_m = (int)(now.tv_usec) - (int)(tv.tv_usec);
	printf("%d:%d %d: I am sleepy\n", time_stamp_s, time_stamp_m, id);
	sleep(1);
	gettimeofday(&now, NULL);
	time_stamp_s = (int)(now.tv_sec) - (int)(tv.tv_sec);
	time_stamp_m = (int)(now.tv_usec) - (int)(tv.tv_usec);
	printf("%d:%d %d: zzzz....\n", time_stamp_s, time_stamp_m, id);
	sleep(1);
	return (NULL);
}

int	main(int ac, char **av)
{
	int	i;
	pthread_t	pt[NUM_PHILO];
	int	ret[NUM_PHILO];
	struct timeval tv;
	//struct timezone tz;
	//pthread_t	pt2;

	gettimeofday(&tv, NULL);
	printf("epoch :%d %d\n", (int)tv.tv_sec, (int)tv.tv_usec);
	i = 0;
	while (i < NUM_PHILO)
	{
		ret[i] = pthread_create(&pt[i], NULL, &life, (void *)&i);
		printf("return value: %d\n", ret[i]);
		printf("thread id: %ld\n", pt[i]);
		i++;
	}
	sleep(10);
	//i = pthread_create(&pt2, NULL, &life, (void *)pt2);
	//printf("return value: %d\n", i);
	//printf("thread id: %ld\n", pt2);
	i = 0;
	while (i < NUM_PHILO)
	{
		pthread_join(pt[i], NULL);
		i++;
	}
	//pthread_join(pt2, NULL);
	return (0);
}