/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philisopfer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:07:25 by athonda           #+#    #+#             */
/*   Updated: 2024/11/25 18:40:56 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "philosopher.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void	*life(void *arg)
{
	printf("I have waken up\n");
	sleep(1);
	printf("I am hungry\n");
	sleep(1);
	return (NULL);
}

int	main(int ac, char **av)
{
	int	i;
	pthread_t	pt;

	i = pthread_create(&pt, NULL, &life, NULL);
	printf("return value: %d\n", i);
	printf("thread id: %ld\n", pt);
	pthread_join(pt, NULL);
	return (0);
}