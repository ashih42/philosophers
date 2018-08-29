/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuel <apuel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 17:01:03 by ashih             #+#    #+#             */
/*   Updated: 2018/08/28 18:57:19 by apuel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void		die(t_philo *philo)
{
	ft_printf("Philosopher #%d dieded!\n", philo->id);
	play_sound(DEATH_SOUND_FILE, philo->path);
	philo->state = PHILO_STATE_DEATH;
	*(philo->died) = true;
	release_wands(philo);
}

static void	rest(t_philo *philo)
{
	int		i;

	ft_printf("Philosopher #%d is resting...\n", philo->id);
	play_sound(REST_SOUND_FILE, philo->path);
	philo->state = PHILO_STATE_REST;
	i = -1;
	while (++i < REST_T)
	{
		if (g_sim_state != SIM_STATE_NORMAL)
			return ;
		if (philo->health == 0)
			return ;
		usleep(1000000);
	}
	philo->state = PHILO_STATE_READY;
}

static void	eat(t_philo *philo)
{
	int		i;

	ft_printf("Philosopher #%d is eating...\n", philo->id);
	play_sound(EAT_SOUND_FILE, philo->path);
	philo->state = PHILO_STATE_EAT;
	i = -1;
	while (++i < EAT_T)
	{
		if (g_sim_state != SIM_STATE_NORMAL)
			return ;
		usleep(1000000);
	}
	philo->health = MAX_LIFE;
	philo->need_to_eat = false;
	if (g_sim_state != SIM_STATE_NORMAL)
		return ;
	release_wands(philo);
	rest(philo);
}

static void	think(t_philo *philo)
{
	int		i;

	ft_printf("Philosopher #%d is thinking...\n", philo->id);
	play_sound(THINK_SOUND_FILE, philo->path);
	philo->state = PHILO_STATE_THINK;
	release_wands(philo);
	i = -1;
	while (++i < THINK_T)
	{
		if (g_sim_state != SIM_STATE_NORMAL)
			return ;
		if (philo->health == 0)
			return ;
		usleep(1000000);
	}
	philo->need_to_eat = true;
	if (g_sim_state != SIM_STATE_NORMAL)
		return ;
	rest(philo);
}

/*
** thread function
*/

void		*philosophize(t_philo *philo)
{
	while (g_sim_state == SIM_STATE_NORMAL)
	{
		if (philo->state == PHILO_STATE_READY)
		{
			if (philo->health == 0)
				return (NULL);
			else if (can_eat(philo))
				eat(philo);
			else if (can_think(philo))
				think(philo);
		}
	}
	return (NULL);
}
