/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:40:10 by athonda           #+#    #+#             */
/*   Updated: 2025/01/10 19:11:26 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/**
 * @file util.c
 * @brief string manipulate
 */

int	ft_is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 30)
		return (1);
	return (0);
}

int	ft_is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

char	*check_num(char *str)
{
	int		len;
	char	*number;

	len = 0;
	while (ft_is_space(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		return (printf("forbiddend negative number\n"), NULL);
	if (!ft_is_digit(*str))
		return (printf("forbidden none number at the begining\n"), NULL);
	number = str;
	while (ft_is_digit(*str))
	{
		str++;
		len++;
	}
	if (*str != '\0')
		return (printf("forbidden none number\n"), NULL);
	if (len > 10)
		return (printf("number shoule be untill INT_MAX \n"), NULL);
	return (number);
}

/**
 * @fn ft_atol
 * @brief input to long integer
 * @param[in] string from command line argument
 * @param[out] long
 *
 */

long	ft_atol(char *str)
{
	char	*number;
	long	num;

	num = 0;
	number = check_num(str);
	if (number == NULL)
		return (0);
	while (*number)
	{
		num = num * 10 + *number - '0';
		number++;
	}
	if (num > 2147483647)
	{
		printf("number should be lower than INT_MAX\n");
		return (0);
	}
	else
		return (num);
}
