/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 17:42:19 by athonda           #+#    #+#             */
/*   Updated: 2025/01/03 00:20:32 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

void	open_semaphore(t_admin *m)
{
	m->stick = sem_open("/chopstick", 0);
	if (m->stick == SEM_FAILED)
		error_exit("sem_open error");
	m->sem_deadcheck = sem_open("/sem_deadicheck", 0);
	if (m->sem_deadcheck == SEM_FAILED)
		error_exit("sem_open error");
	m->sem_print = sem_open("/sem_print", 0);
	if (m->sem_print == SEM_FAILED)
		error_exit("sem_open error");
	m->sem_count = sem_open("/sem_count", 0);
	if (m->sem_count == SEM_FAILED)
		error_exit("sem_open error");
}

void	clean_semaphore(t_admin *m)
{
	sem_close(m->stick);
	sem_close(m->sem_deadcheck);
	sem_close(m->sem_print);
	sem_close(m->sem_count);
	sem_unlink("/chopstick");
	sem_unlink("/sem_deadcheck");
	sem_unlink("/sem_print");
	sem_unlink("/sem_count");
}
