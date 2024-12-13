/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:07:25 by athonda           #+#    #+#             */
/*   Updated: 2024/12/13 08:23:44 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"


void	set_arg(t_admin *m, char **av)
{
	m->nb_philo = ft_atol(av[1]);
	m->time_die = ft_atol(av[2]);
	m->time_eat = ft_atol(av[3]);
	m->time_sleep = ft_atol(av[4]);
	if (av[5])
		m->max_eat = ft_atol(av[5]);
}

int	main(int ac, char **av)
{
	unsigned int	i;
	int	ret;
	t_philo	p[200];
	t_admin	m;

	if (ac < 5 || ac > 6)
	{
		error_exit("wrong argument: ex) 5 800 200 200 [3]\n");
		return (1);
	}
	init_admin(&m, &p[0]);
	set_arg(&m, av);
	if (init_mutex(&m))
		return (0);
	pthread_mutex_lock(&m.mutex);
	i = 1;
	while (i <= m.nb_philo)
	{
		init_philo(&p[i], i, &m);
		ret = pthread_create(&p[i].pt, NULL, &constraint, &p[i]);
		if (ret != 0)
			return (0);
		usleep(100);
		i++;
	}
	ret = pthread_create(&m.pt_monitor, NULL, &monitoring, &m);
	if (ret != 0)
		return (0);
	m.start = get_time();
	pthread_mutex_unlock(&m.mutex);
	pthread_join(m.pt_monitor, NULL);
	i = 1;
	while (i <= m.nb_philo)
	{
		pthread_join(p[i].pt, NULL);
		i++;
	}
	return (0);
}