/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_actors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 01:11:40 by ashih             #+#    #+#             */
/*   Updated: 2018/08/26 22:20:46 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int				init_threads(t_master *m)
{
	int			i;

	i = -1;
	while (++i < m->n)
	{
		if (pthread_create(&m->philo_th[i], NULL,
			(void *(*)(void *))&philosophize, &m->philo[i]))
			return (ft_puterror("pthread_create() failed", 0, -1));
	}
	return (0);
}

static void		init_wand(t_wand *wand, int x, int y)
{
	pthread_mutex_init(&wand->mutex, NULL);
	wand->default_rect = (SDL_Rect){x, y, PHILO_SIZE, PHILO_SIZE};
	wand->rect = wand->default_rect;
}

static void		init_philo(t_philo *philo, int x, int y, t_master *m)
{
	philo->rect = (SDL_Rect){x, y, PHILO_SIZE, PHILO_SIZE};
	philo->health = MAX_LIFE;
	philo->has_left_wand = false;
	philo->has_right_wand = false;
	philo->state = PHILO_STATE_READY;
	philo->path = m->path;
	philo->died = &m->someone_died;
	philo->need_to_eat = (philo->id % 2 == 0);
}

static void		init_seats(t_master *m)
{
	int			scr_x;
	int			scr_y;
	int			i;

	i = -1;
	while (++i < (m->n * 2))
	{
		scr_x = (int)((cos(M_PI * i / m->n) + 1.0) / 2.0 *
			(SCREEN_WIDTH - 2 * PHILO_SIZE) + PHILO_SIZE / 2);
		scr_y = (int)((sin(M_PI * i / m->n) + 1.0) / 2.0 *
			(SCREEN_HEIGHT - 2 * PHILO_SIZE) + PHILO_SIZE / 2);
		if (i % 2 == 0)
		{
			init_philo(&m->philo[i / 2], scr_x, scr_y, m);
			m->philo[i / 2].id = i / 2;
			m->philo[i / 2].left_wand = &m->wand[i / 2];
			m->philo[i / 2].right_wand = &m->wand[POS_MODDULO(i / 2 - 1, m->n)];
		}
		else
		{
			init_wand(&m->wand[i / 2], scr_x, scr_y);
			m->wand[i / 2].id = i / 2;
		}
	}
}

int				init_actors(t_master *m)
{
	if (!(m->philo = ft_memalloc(sizeof(t_philo) * m->n)) ||
		!(m->wand = ft_memalloc(sizeof(t_wand) * m->n)) ||
		!(m->philo_th = ft_memalloc(sizeof(pthread_t) * m->n)))
		return (ft_puterror(ERROR_MEMORY, 0, -1));
	init_seats(m);
	return (0);
}
