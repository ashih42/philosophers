/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 08:58:42 by ashih             #+#    #+#             */
/*   Updated: 2018/08/26 22:12:44 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

enum e_sim_state	g_sim_state = SIM_STATE_NORMAL;

int					main(int argc, char **argv)
{
	t_master		m;
	int				i;

	srand(time(NULL));
	ft_bzero(&m, sizeof(t_master));
	if (!(1 <= argc && argc <= 2))
		return (ft_puterror(ERROR_USAGE, 0, EXIT_FAILURE));
	if (argc == 2)
	{
		if (ft_atoi_check(argv[1], &m.n) || !(2 <= m.n && m.n <= 100))
			return (ft_puterror(ERROR_NUM, 0, EXIT_FAILURE));
	}
	else
		m.n = NUM_TEX;
	if (init_sdl(&m) || init_actors(&m) || init_threads(&m))
		return (free_all(&m, EXIT_FAILURE));
	render_loop(&m);
	i = -1;
	while (++i < m.n)
		pthread_join(m.philo_th[i], NULL);
	return (free_all(&m, EXIT_SUCCESS));
}
