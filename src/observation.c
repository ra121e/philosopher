/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 15:16:14 by athonda           #+#    #+#             */
/*   Updated: 2024/12/21 15:29:05 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file observation.c
 * @brief several checking status functions
 */

#include "philosopher.h"

/**
 * @fn int checking(t_philo *p)
 * @brief check dead status in admin struct m
 * @param[in]	p each philo struct
 * @param[out]	1(DEAD) or 0(ALIVE)
 */

int	checking(t_philo *p)
{
	pthread_mutex_lock(&p->m->mutex_dead);
	if (p->m->dead == DEAD)
	{
		pthread_mutex_unlock(&p->m->mutex_dead);
		return (DEAD);
	}
	pthread_mutex_unlock(&p->m->mutex_dead);
	return (ALIVE);
}
