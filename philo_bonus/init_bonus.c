/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:01:19 by athonda           #+#    #+#             */
/*   Updated: 2025/01/06 10:26:06 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

/**
 * @fn init_admin(t_admin *m, t_philo *p)
 * @brief initialize admin struct
 * @param[in]	m pointer to general info struct
 * @param[in]	p pointer to the beginning of philo struct array
 *
 */

void	init_admin(t_admin *m, t_philo *p)
{
	m->epoch = 0;
	m->start = 0;
	m->dead = 0;
	m->p = p;
	m->stick = NULL;
	m->sem_dead = NULL;
	m->sem_print = NULL;
	m->sem_count = NULL;
	m->sem_time = NULL;
	m->sem_finish = NULL;
}

/**
 * @fn init_philo(t_philo *p, int i, t_admin *m)
 * @brief initialize philo struct array
 * @param[in]	p pointer to philo array
 * @param[in]	i index num of philo array
 * @param[in]	m pointer to general info struct
 * @note
 */

void	init_philo(t_philo *p, int i)
{
	p->id = i;
	p->start = 0;
	p->last_supper = 0;
	p->pt = 0;
	p->status = 0;
	p->tv.tv_sec = 0;
	p->tv.tv_usec = 0;
	p->counter = 0;
	p->full = 0;
}
