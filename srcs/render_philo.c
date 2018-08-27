/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 21:42:44 by ashih             #+#    #+#             */
/*   Updated: 2018/08/26 21:57:08 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void		display_philo_id(t_philo *philo, t_master *m)
{
	SDL_Rect	rect;

	rect = philo->rect;
	rect.x += 90;
	rect.y += 90;
	render_num((uint32_t)philo->id, (SDL_Color){255, 255, 255, 255}, rect, m);
}

static void		display_health_bar(t_philo *philo, SDL_Color color,
	SDL_Rect rect, t_master *m)
{
	uint32_t	health_adjusted;
	uint32_t	i;

	health_adjusted = CHANGE(philo->health, 0, MAX_LIFE, 0, HEALTH_BAR_WIDTH);
	SDL_SetRenderDrawColor(m->ren, color.r, color.g, color.b, color.a);
	i = 0;
	while (i < health_adjusted)
	{
		SDL_RenderDrawLine(m->ren, rect.x + i, rect.y,
			rect.x + i, rect.y + HEALTH_BAR_HEIGHT);
		i++;
	}
	SDL_SetRenderDrawColor(m->ren, 255, 255, 255, 255);
	SDL_RenderDrawLine(m->ren, rect.x, rect.y,
		rect.x + HEALTH_BAR_WIDTH, rect.y);
	SDL_RenderDrawLine(m->ren, rect.x, rect.y + HEALTH_BAR_HEIGHT,
		rect.x + HEALTH_BAR_WIDTH, rect.y + HEALTH_BAR_HEIGHT);
	SDL_RenderDrawLine(m->ren, rect.x, rect.y,
		rect.x, rect.y + HEALTH_BAR_HEIGHT);
	SDL_RenderDrawLine(m->ren, rect.x + HEALTH_BAR_WIDTH, rect.y,
		rect.x + HEALTH_BAR_WIDTH, rect.y + HEALTH_BAR_HEIGHT);
}

static void		display_health(t_philo *philo, t_master *m)
{
	SDL_Color	color;
	SDL_Rect	rect;

	rect = philo->rect;
	rect.y -= 15;
	if (philo->health < (MAX_LIFE / 3))
		color = (SDL_Color){255, 0, 0, 255};
	else if (philo->health < (MAX_LIFE * 2 / 3))
		color = (SDL_Color){255, 255, 0, 255};
	else
		color = (SDL_Color){0, 255, 0, 255};
	if (m->show_health_bar)
		display_health_bar(philo, color, rect, m);
	else
		render_num(philo->health, color, rect, m);
}

void			render_philo(t_philo *philo, t_master *m)
{
	int			id;

	id = philo->id % NUM_TEX;
	if (philo->state == PHILO_STATE_READY)
	{
		if (philo->health >= (MAX_LIFE) / 3)
			render_tex(m->ready_tex[id], &philo->rect, m->ren);
		else
			render_tex(m->low_health_tex[id], &philo->rect, m->ren);
	}
	else if (philo->state == PHILO_STATE_EAT)
		render_tex(m->eat_tex[id], &philo->rect, m->ren);
	else if (philo->state == PHILO_STATE_THINK)
		render_tex(m->think_tex[id], &philo->rect, m->ren);
	else if (philo->state == PHILO_STATE_REST)
		render_tex(m->rest_tex[id], &philo->rect, m->ren);
	else if (philo->state == PHILO_STATE_DEATH)
		render_tex(m->death_tex[id], &philo->rect, m->ren);
	display_health(philo, m);
	display_philo_id(philo, m);
}
