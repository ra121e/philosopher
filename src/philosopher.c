/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:07:25 by athonda           #+#    #+#             */
/*   Updated: 2024/12/19 00:48:42 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	set_arg(t_admin *m, char **av)
{
	m->nb_philo = ft_atol(av[1]);
	if (m->nb_philo > 200)
	{
		printf("Do not test with more than 200 philo!\n");
		return (0);
	}
	m->time_die = ft_atol(av[2]);
	m->time_eat = ft_atol(av[3]);
	m->time_sleep = ft_atol(av[4]);
	if (av[5])
		m->max_eat = ft_atol(av[5]);
	if (m->time_die < 60 || m->time_eat < 60 || m->time_sleep < 60)
	{
		printf("Do not test with time set to values lower than 60 ms!\n");
		return (0);
	}
	return (1);
}

/**
 * @fn start_simulation(t_admin *m, t_philo *p)
 * @brief create thread repeatly
 * @param[in]	m general data storage
 * @param[in]	p philo data storage
 * @param[out]	NULL or int
 * @note
	- covered by mutex to make thread run simultaniously
	- just before unlock mutex, get time and record it
 */

void	start_simulation(t_admin *m, t_philo *p)
{
	unsigned int	i;
	int				ret;

	pthread_mutex_lock(&m->mutex_start);
	i = 1;
	while (i <= m->nb_philo)
	{
		init_philo(&p[i], i, m);
		ret = pthread_create(&p[i].pt, NULL, &constraint, &p[i]);
		if (ret != 0)
			return ;
		usleep(100);
		i++;
	}
	ret = pthread_create(&m->pt_monitor, NULL, &monitoring, m);
	if (ret != 0)
		return ;
	m->start = get_time();
	pthread_mutex_unlock(&m->mutex_start);
}

int	main(int ac, char **av)
{
	unsigned int	i;
	t_philo			p[250];
	t_admin			m;

	if (ac < 5 || ac > 6)
	{
		error_exit("wrong argument: ex) 5 800 200 200 [3]\n");
		return (1);
	}
	init_admin(&m, &p[0]);
	if (!set_arg(&m, av))
		return (0);
	if (init_mutex(&m))
		return (0);
	start_simulation(&m, p);
	pthread_join(m.pt_monitor, NULL);
	i = 1;
	while (i <= m.nb_philo)
	{
		pthread_join(p[i].pt, NULL);
		i++;
	}
	return (0);
}
