/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 15:12:24 by ashih             #+#    #+#             */
/*   Updated: 2018/08/24 19:08:54 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

char			*g_tex_files[NUM_TEX][6] =
{
	{
		"images/apple/eyebrow.png",
		"images/apple/fearful.png",
		"images/apple/laughing.png",
		"images/apple/skull.png",
		"images/apple/sleepy.png",
		"images/apple/thinking.png"
	},
	{
		"images/emojiOne/eyebrow.png",
		"images/emojiOne/fearful.png",
		"images/emojiOne/laughing.png",
		"images/emojiOne/skull.png",
		"images/emojiOne/sleepy.png",
		"images/emojiOne/thinking.png"
	},
	{
		"images/facebook/eyebrow.png",
		"images/facebook/fearful.png",
		"images/facebook/laughing.png",
		"images/facebook/skull.png",
		"images/facebook/sleepy.png",
		"images/facebook/thinking.png"
	},
	{
		"images/google/eyebrow.png",
		"images/google/fearful.png",
		"images/google/laughing.png",
		"images/google/skull.png",
		"images/google/sleepy.png",
		"images/google/thinking.png"
	},
	{
		"images/microsoft/eyebrow.png",
		"images/microsoft/fearful.png",
		"images/microsoft/laughing.png",
		"images/microsoft/skull.png",
		"images/microsoft/sleepy.png",
		"images/microsoft/thinking.png"
	},
	{
		"images/samsung/eyebrow.png",
		"images/samsung/fearful.png",
		"images/samsung/laughing.png",
		"images/samsung/skull.png",
		"images/samsung/sleepy.png",
		"images/samsung/thinking.png"
	},
	{
		"images/twitter/eyebrow.png",
		"images/twitter/fearful.png",
		"images/twitter/laughing.png",
		"images/twitter/skull.png",
		"images/twitter/sleepy.png",
		"images/twitter/thinking.png"
	},
};

static void	scramble_order(t_master *m)
{
	int		i;
	int		j;

	i = -1;
	while (++i < NUM_TEX)
	{
		j = rand() % NUM_TEX;
		SWAP(m->wand_tex[i], m->wand_tex[j], SDL_Texture *);
		j = rand() % NUM_TEX;
		SWAP(m->ready_tex[i], m->ready_tex[j], SDL_Texture *);
		SWAP(m->low_health_tex[i], m->low_health_tex[j], SDL_Texture *);
		SWAP(m->eat_tex[i], m->eat_tex[j], SDL_Texture *);
		SWAP(m->think_tex[i], m->think_tex[j], SDL_Texture *);
		SWAP(m->rest_tex[i], m->rest_tex[j], SDL_Texture *);
		SWAP(m->death_tex[i], m->death_tex[j], SDL_Texture *);
	}
}

static int	init_philo_tex(t_master *m)
{
	int		i;

	i = -1;
	while (++i < NUM_TEX)
	{
		if (!(m->ready_tex[i] = load_tex(g_tex_files[i][0], m)) ||
			!(m->low_health_tex[i] = load_tex(g_tex_files[i][1], m)) ||
			!(m->eat_tex[i] = load_tex(g_tex_files[i][2], m)) ||
			!(m->think_tex[i] = load_tex(g_tex_files[i][5], m)) ||
			!(m->rest_tex[i] = load_tex(g_tex_files[i][4], m)) ||
			!(m->death_tex[i] = load_tex(g_tex_files[i][3], m)))
			return (-1);
	}
	return (0);
}

static int	init_tex(t_master *m)
{
	if (init_philo_tex(m) ||
		!(m->wand_tex[0] = load_tex(WAND0_TEX_FILE, m)) ||
		!(m->wand_tex[1] = load_tex(WAND1_TEX_FILE, m)) ||
		!(m->wand_tex[2] = load_tex(WAND2_TEX_FILE, m)) ||
		!(m->wand_tex[3] = load_tex(WAND3_TEX_FILE, m)) ||
		!(m->wand_tex[4] = load_tex(WAND4_TEX_FILE, m)) ||
		!(m->wand_tex[5] = load_tex(WAND5_TEX_FILE, m)) ||
		!(m->wand_tex[6] = load_tex(WAND6_TEX_FILE, m)) ||
		!(m->dance_tex = load_tex(DANCE_TEX_FILE, m)) ||
		!(m->died_tex = load_tex(DIED_TEX_FILE, m)))
		return (-1);
	else
		return (0);
}

int			init_sdl(t_master *m)
{
	if (SDL_Init(SDL_INIT_VIDEO))
		return (ft_puterror("SDL_Init() failed", 0, -1));
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
		return (ft_puterror("IMG_Init() failed", 0, -1));
	if (TTF_Init())
		return (ft_puterror("TTF_Init() failed", 0, -1));
	if (!(m->path = SDL_GetBasePath()) ||
		!(m->win = SDL_CreateWindow("Philosophers", 100, 100,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN)) ||
		!(m->ren = SDL_CreateRenderer(m->win, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) ||
		!(m->font = load_font(FONT_FILE, m, FONT_SIZE)) ||
		init_tex(m))
		return (ft_puterror(ERROR_MEMORY, 0, -1));
	scramble_order(m);
	return (0);
}
