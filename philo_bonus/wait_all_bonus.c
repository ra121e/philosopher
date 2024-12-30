/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_all_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:50:34 by athonda           #+#    #+#             */
/*   Updated: 2024/12/30 14:11:25 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

void	wait_all(void)
{
	pid_t	pid;
	int		wstatus;

	while (1)
	{
		pid = waitpid(-1, &wstatus, 0);
		if (pid == -1)
			return ;
	}
}
