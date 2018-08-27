/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 10:26:53 by ashih             #+#    #+#             */
/*   Updated: 2018/08/26 21:53:58 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	free_textures(t_master *m)
{
	int		i;

	i = -1;
	while (++i < NUM_TEX)
	{
		SDL_DestroyTexture(m->ready_tex[i]);
		SDL_DestroyTexture(m->low_health_tex[i]);
		SDL_DestroyTexture(m->eat_tex[i]);
		SDL_DestroyTexture(m->think_tex[i]);
		SDL_DestroyTexture(m->rest_tex[i]);
		SDL_DestroyTexture(m->death_tex[i]);
		SDL_DestroyTexture(m->wand_tex[i]);
	}
	SDL_DestroyTexture(m->dance_tex);
	SDL_DestroyTexture(m->died_tex);
}

int			free_all(t_master *m, int ret)
{
	int		i;

	i = -1;
	while (++i < m->n)
		pthread_mutex_destroy(&m->wand[i].mutex);
	ft_memdel((void **)&m->philo);
	ft_memdel((void **)&m->wand);
	ft_memdel((void **)&m->philo_th);
	free_textures(m);
	SDL_DestroyRenderer(m->ren);
	SDL_DestroyWindow(m->win);
	TTF_CloseFont(m->font);
	ft_strdel(&m->path);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	return (ret);
}
