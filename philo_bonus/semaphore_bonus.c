/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 17:42:19 by athonda           #+#    #+#             */
/*   Updated: 2025/01/06 10:26:32 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

int	init_semaphore(t_admin *m)
{
	sem_unlink("/chopstick");
	sem_unlink("/sem_dead");
	sem_unlink("/sem_print");
	sem_unlink("/sem_count");
	sem_unlink("/sem_time");
	sem_unlink("/sem_finish");
	m->stick = sem_open("/chopstick", O_CREAT | O_EXCL, 0644, m->nb_philo);
	if (m->stick == SEM_FAILED)
		return (printf("sem_open error"), 1);
	m->sem_dead = sem_open("/sem_dead", O_CREAT | O_EXCL, 0644, 0);
	if (m->sem_dead == SEM_FAILED)
		return (printf("sem_open error"), 1);
	m->sem_print = sem_open("/sem_print", O_CREAT | O_EXCL, 0644, 1);
	if (m->sem_print == SEM_FAILED)
		return (printf("sem_open error"), 1);
	m->sem_count = sem_open("/sem_count", O_CREAT | O_EXCL, 0644, 0);
	if (m->sem_count == SEM_FAILED)
		return (printf("sem_open error"), 1);
	m->sem_time = sem_open("/sem_time", O_CREAT | O_EXCL, 0644, 1);
	if (m->sem_time == SEM_FAILED)
		return (printf("sem_open error"), 1);
	m->sem_finish = sem_open("/sem_finish", O_CREAT | O_EXCL, 0644, 1);
	if (m->sem_finish == SEM_FAILED)
		return (printf("sem_open error"), 1);
	return (0);
}

void	clean_semaphore(t_admin *m)
{
	if (m->stick)
		sem_close(m->stick);
	if (m->sem_dead)
		sem_close(m->sem_dead);
	if (m->sem_print)
		sem_close(m->sem_print);
	if (m->sem_count)
		sem_close(m->sem_count);
	if (m->sem_time)
		sem_close(m->sem_time);
	if (m->sem_finish)
		sem_close(m->sem_finish);
	sem_unlink("/chopstick");
	sem_unlink("/sem_dead");
	sem_unlink("/sem_print");
	sem_unlink("/sem_count");
	sem_unlink("/sem_time");
	sem_unlink("/sem_finish");
}
