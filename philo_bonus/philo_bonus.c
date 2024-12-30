/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 22:55:41 by athonda           #+#    #+#             */
/*   Updated: 2024/12/30 20:13:56 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

/*
int	set_arg(t_admin *m, char **av)
{
	m->nb_philo = ft_atol(av[1]);
	if (m->nb_philo <= 0)
	{
		printf("philosopher number should be more than 0\n");
		return (0);
	}
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
*/

void	start_simulation(t_admin *m, t_philo *p)
{
	unsigned int	i;

	i = 1;
	while (i <= 5)
	{
		p[i].pid = fork();
		if (p[i].pid < 0)
			return ;
		if (p[i].pid == 0)
		{
			init_philo(&p[i], i);
			m->start = get_time();
			p[i].id = i;
			constraint(m, &p[i]);
			exit(1);
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	int				status;
	t_admin			m;
	t_philo			p[250];

	(void)av;
	(void)ac;
//	if (ac < 5 || ac > 6)
//	{
//		printf("wrong argumne: ex) -> 5 800 200 200 [3]\n");
//		return (1);
//	}
	init_admin(&m);
	start_simulation(&m, p);
//	waitpid(p[0].pid, &status, 0);
	wait_all();
	sem_close(m.stick);
	sem_unlink("/chopstick");
	return (WEXITSTATUS(status));
//	t_philo			p[250];
//	t_admin			m;

//	if (ac < 5 || ac > 6)
//	{
//		printf("wrong argument: ex) 5 800 200 200 [3]\n");
//		return (1);
//	}
//	init_admin(&m, &p[0]);
//	if (!set_arg(&m, av))
//		return (0);
//	start_simulation(&m, p);
	return (0);
}