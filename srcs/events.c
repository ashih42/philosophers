/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 10:34:36 by ashih             #+#    #+#             */
/*   Updated: 2018/08/23 21:30:39 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void			handle_events(t_master *m)
{
	SDL_Event	e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			g_sim_state = SIM_STATE_QUIT;
		else if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_ESCAPE)
				g_sim_state = SIM_STATE_QUIT;
			else if (e.key.keysym.sym == SDLK_h)
				m->show_health_bar = !m->show_health_bar;
		}
	}
}
