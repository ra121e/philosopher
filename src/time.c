/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:54:38 by athonda           #+#    #+#             */
/*   Updated: 2024/12/14 20:32:20 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/**
 * @fn	long get_time(void)
 * @brief return milli-second from gettimeofday()
 * @param[in]	none
 * @param[out]	long milli second
 * @note gettimeofday gives us second since 1970/1/1 0:00:00
 * it makes the year 2038 problem
 */

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, 0);
	return ((long)tv.tv_sec * 1000 + (long)tv.tv_usec / 1000);
}
