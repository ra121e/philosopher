/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constraint_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:41:53 by athonda           #+#    #+#             */
/*   Updated: 2025/01/01 09:25:47 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file constraints_bonus.c
 * @brief condition limits the degrees of freedom of a system
 * @note
 */

#include "philosopher_bonus.h"

/**
 * @fn int solo_dining(t_philo *p)
 * @brief in case of object number is one
 */

int	solo_dining(t_admin *m, t_philo *p)
{
	if (m->nb_philo == 1)
	{
		taking(m, p);
		usleep(m->time_die);
		return (1);
	}
	return (0);
}

/**
 * @fn void *constraint(void *arg)
 * @brief environment constraint as start routine
 * @param[in] arg: struct for object constants
 * @param[out] void * basically NULL
 * @return NULL
 */

void	*motion(t_admin *m, t_philo *p)
{
	p->last_supper = m->start;
	if (solo_dining(m, p) == 1)
		sem_wait(m->stick);
	while (1)
	{
		if (thinking(m, p) == 1)
			return (NULL);
		if (eating(m, p) == 1)
			break ;
		if (sleeping(m, p) == 1)
			return (NULL);
		if (p->full == 1)
			exit(1);
	}
	exit(1);
}
