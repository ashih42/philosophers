/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 16:42:18 by ashih             #+#    #+#             */
/*   Updated: 2018/08/26 21:55:02 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void		render_wand(t_wand *wand, t_master *m)
{
	render_tex(m->wand_tex[wand->id % NUM_TEX], &wand->rect, m->ren);
}

static void		report_timeout(t_master *m)
{
	g_sim_state = SIM_STATE_TIMEOUT;
	ft_printf("\nTIMEOUT\n");
	if (m->someone_died)
	{
		ft_printf("Someone dieded.\n");
		play_sound(DIED_SOUND_FILE, m->path);
	}
	else
	{
		ft_printf("Now, it is time... To DAAAAAAAANCE!!!\n");
		play_sound(DANCE_SOUND_FILE, m->path);
	}
}

static void		clock_tick(t_master *m)
{
	int				i;

	if (g_sim_state == SIM_STATE_NORMAL)
	{
		m->curr_time = SDL_GetTicks() / 1000;
		if (m->curr_time > m->prev_time)
		{
			i = -1;
			while (++i < m->n)
			{
				if (!(m->philo[i].state == PHILO_STATE_EAT ||
					m->philo[i].state == PHILO_STATE_DEATH) &&
					m->philo[i].health != 0)
					m->philo[i].health--;
				if (m->philo[i].health == 0 &&
					m->philo[i].state != PHILO_STATE_DEATH)
					die(&m->philo[i]);
			}
			m->prev_time = m->curr_time;
		}
		if (m->curr_time == TIMEOUT)
			report_timeout(m);
	}
	render_num(m->curr_time, (SDL_Color){255, 255, 255, 255},
		(SDL_Rect){0, 0, 0, 0}, m);
}

static void		render_timeout_tex(t_master *m)
{
	SDL_Texture	*tex;
	SDL_Rect	rect;

	tex = (m->someone_died) ? m->died_tex : m->dance_tex;
	SDL_QueryTexture(tex, NULL, NULL, &rect.w, &rect.h);
	rect.x = SCREEN_WIDTH / 2 - rect.w / 2;
	rect.y = SCREEN_HEIGHT / 2 - rect.h / 2;
	render_tex(tex, &rect, m->ren);
}

void			render_loop(t_master *m)
{
	int			i;

	while (g_sim_state != SIM_STATE_QUIT)
	{
		handle_events(m);
		SDL_SetRenderDrawColor(m->ren, 0, 0, 0, 255);
		SDL_RenderClear(m->ren);
		if (g_sim_state == SIM_STATE_TIMEOUT)
			render_timeout_tex(m);
		i = -1;
		while (++i < m->n)
			render_wand(&m->wand[i], m);
		i = -1;
		while (++i < m->n)
			render_philo(&m->philo[i], m);
		clock_tick(m);
		SDL_RenderPresent(m->ren);
	}
}
