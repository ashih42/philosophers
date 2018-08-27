/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 08:58:49 by ashih             #+#    #+#             */
/*   Updated: 2018/08/26 22:23:32 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "libft.h"
# include <pthread.h>
# include <SDL.h>
# include <SDL_image.h>
# include <SDL_ttf.h>
# include <math.h>
# include <stdbool.h>

# define MAX_LIFE			60
# define EAT_T				6
# define THINK_T			11
# define REST_T				7
# define TIMEOUT			100

# define SCREEN_WIDTH		1000
# define SCREEN_HEIGHT		1000
# define PHILO_SIZE			100
# define HEALTH_BAR_WIDTH	100
# define HEALTH_BAR_HEIGHT	10

# define FONT_FILE			"fonts/sample_font.ttf"
# define FONT_SIZE			24

# define NUM_TEX			7

# define WAND0_TEX_FILE		"images/wands/burrito.png"
# define WAND1_TEX_FILE		"images/wands/donut.png"
# define WAND2_TEX_FILE		"images/wands/hamburger.png"
# define WAND3_TEX_FILE		"images/wands/hotdog.png"
# define WAND4_TEX_FILE		"images/wands/pizza.png"
# define WAND5_TEX_FILE		"images/wands/shortcake.png"
# define WAND6_TEX_FILE		"images/wands/taco.png"

# define DANCE_TEX_FILE		"images/dance.png"
# define DIED_TEX_FILE		"images/died.png"

# define EAT_SOUND_FILE		"sounds/om_nom.mp3"
# define THINK_SOUND_FILE	"sounds/huh.wav"
# define REST_SOUND_FILE	"sounds/winXP_shutdown.mp3"
# define DEATH_SOUND_FILE	"sounds/minecraft_ugh.wav"

# define DANCE_SOUND_FILE	"sounds/dance.aiff"
# define DIED_SOUND_FILE	"sounds/died.aiff"

# define ERROR_USAGE		"usage: philo [num_philo]"
# define ERROR_NUM			"num_philo must be a positive integer in [2, 100]"
# define ERROR_MEMORY		"Out of memory"

# define POS_MODDULO(i, n)	(((i) % (n) + (n)) % (n))

# define SWAP(a, b, T)		{T temp = a; a = b; b = temp;}

/*
** Transform x in [min, max] to some new value in [a, b]
*/
# define CHANGE(x, min, max, a, b) (((b)-(a))*((x)-(min))/((max)-(min)))+(a)

typedef struct					s_wand
{
	int							id;
	pthread_mutex_t				mutex;
	SDL_Rect					default_rect;
	SDL_Rect					rect;
}								t_wand;

enum							e_philo_state
{
	PHILO_STATE_DEATH,
	PHILO_STATE_READY,
	PHILO_STATE_EAT,
	PHILO_STATE_THINK,
	PHILO_STATE_REST
};

typedef struct					s_philo
{
	int							id;
	volatile enum e_philo_state	state;
	volatile uint32_t			health;
	bool						has_left_wand;
	bool						has_right_wand;
	t_wand						*left_wand;
	t_wand						*right_wand;
	SDL_Rect					rect;
	char						*path;
	bool						*died;
	bool						need_to_eat;
}								t_philo;

typedef struct					s_master
{
	int							n;

	pthread_t					*philo_th;
	t_philo						*philo;
	t_wand						*wand;

	SDL_Window					*win;
	SDL_Renderer				*ren;
	TTF_Font					*font;

	SDL_Texture					*ready_tex[NUM_TEX];
	SDL_Texture					*low_health_tex[NUM_TEX];
	SDL_Texture					*eat_tex[NUM_TEX];
	SDL_Texture					*think_tex[NUM_TEX];
	SDL_Texture					*rest_tex[NUM_TEX];
	SDL_Texture					*death_tex[NUM_TEX];

	SDL_Texture					*wand_tex[NUM_TEX];

	SDL_Texture					*dance_tex;
	SDL_Texture					*died_tex;

	char						*path;

	bool						show_health_bar;
	bool						someone_died;

	uint32_t					curr_time;
	uint32_t					prev_time;

}								t_master;

enum							e_sim_state
{
	SIM_STATE_NORMAL,
	SIM_STATE_TIMEOUT,
	SIM_STATE_QUIT,
};

extern enum e_sim_state			g_sim_state;

/*
** events.c
*/
void							handle_events(t_master *m);

/*
** font.c
*/
int								render_num(
	uint32_t num, SDL_Color color, SDL_Rect rect, t_master *m);
int								render_str(
	char *message, SDL_Color color, SDL_Rect rect, t_master *m);
TTF_Font						*load_font(
	char *filename, t_master *m, int size);

/*
** freedom.c
*/
int								free_all(t_master *m, int ret);

/*
** init_actors.c
*/
int								init_threads(t_master *m);
int								init_actors(t_master *m);

/*
** init_sdl.c
*/
int								init_sdl(t_master *m);

/*
** main.c
*/

/*
** philo_util.c
*/
bool							can_eat(t_philo *philo);
bool							can_think(t_philo *philo);
void							release_wands(t_philo *philo);

/*
** philosophize.c
*/
void							die(t_philo *philo);
void							*philosophize(t_philo *philo);

/*
** render.c
*/
void							render_loop(t_master *m);

/*
** render_philo.c
*/
void							render_philo(t_philo *philo, t_master *m);

/*
** sound.c
*/
void							play_sound(char *filename, char *path);

/*
** texture.c
*/
SDL_Texture						*load_tex(char *filename, t_master *m);
void							render_tex(
	SDL_Texture *tex, SDL_Rect *rect, SDL_Renderer *ren);

#endif
