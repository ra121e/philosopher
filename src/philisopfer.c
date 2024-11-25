/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philisopfer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:07:25 by athonda           #+#    #+#             */
/*   Updated: 2024/11/25 19:44:52 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "philosopher.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

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
	pthread_t	pt;
	pthread_t	pt2;


	i = pthread_create(&pt, NULL, &life, (void *)pt);
	printf("return value: %d\n", i);
	printf("thread id: %ld\n", pt);
	sleep(1);
	i = pthread_create(&pt2, NULL, &life, (void *)pt2);
	pthread_join(pt, NULL);
	pthread_join(pt2, NULL);
	return (0);
}