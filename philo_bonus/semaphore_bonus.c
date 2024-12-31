/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 17:42:19 by athonda           #+#    #+#             */
/*   Updated: 2024/12/31 17:56:18 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

void	clean_semaphore(t_admin *m)
{
	sem_close(m->stick);
	sem_close(m->sem_dead);
	sem_close(m->sem_print);
	sem_close(m->sem_count);
	sem_unlink("/chopstick");
	sem_unlink("/sem_dead");
	sem_unlink("/sem_print");
	sem_unlink("/sem_count");

}