/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:02:25 by athonda           #+#    #+#             */
/*   Updated: 2024/12/10 21:23:24 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	error_exit(char *str)
{
	while (*str)
		write(2, str++, 1);
}


void	err(char *str)
{
	while (*str)
		write(2, str++, 1);
	exit(EXIT_FAILURE);
}