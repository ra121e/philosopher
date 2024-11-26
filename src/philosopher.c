/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:07:25 by athonda           #+#    #+#             */
/*   Updated: 2024/11/26 21:13:43 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "philosopher.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#define NUM_PHILO 5

void	*life(void *arg)
{
	pthread_t	id;

	id = (pthread_t)arg;
	printf("%ld: I have woken up\n", id);
	sleep(1);
	printf("%ld: I am hungry\n", id);
	sleep(1);
	printf("%ld: I have picked up forks\n", id);
	sleep(1);
	printf("%ld: I am eating\n", id);
	sleep(1);
	printf("%ld: I am enough\n", id);
	sleep(1);
	printf("%ld: I have returned forks\n", id);
	sleep(1);
	printf("%ld: I am thinking\n", id);
	sleep(1);
	printf("%ld: I am sleepy\n", id);
	sleep(1);
	printf("%ld: zzzz....\n", id);
	sleep(1);
	return (NULL);
}

int	main(int ac, char **av)
{
	int	i;
	pthread_t	pt[NUM_PHILO];
	int	ret[NUM_PHILO];
	//pthread_t	pt2;

	i = 0;
	while (i < NUM_PHILO)
	{
		ret[i] = pthread_create(&pt[i], NULL, &life, (void *)pt[i]);
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