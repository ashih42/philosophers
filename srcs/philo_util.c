/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 11:10:38 by ashih             #+#    #+#             */
/*   Updated: 2018/08/26 22:07:44 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	take_wand(t_philo *philo, t_wand *wand)
{
	if (pthread_mutex_trylock(&wand->mutex) == 0)
	{
		wand->rect.x = (wand->default_rect.x + philo->rect.x * 2) / 3;
		wand->rect.y = (wand->default_rect.y + philo->rect.y * 2) / 3;
		return (true);
	}
	else
		return (false);
}

/*
** Precondition: Currently have no wands
*/

bool	can_eat(t_philo *philo)
{
	if (!philo->need_to_eat)
		return (false);
	if (!philo->has_left_wand && take_wand(philo, philo->left_wand))
		philo->has_left_wand = true;
	if (!philo->has_right_wand && take_wand(philo, philo->right_wand))
		philo->has_right_wand = true;
	if (philo->has_left_wand && philo->has_right_wand)
		return (true);
	else
	{
		release_wands(philo);
		return (false);
	}
}

/*
** Precondition: Currently have no wands
*/

bool	can_think(t_philo *philo)
{
	if (philo->need_to_eat)
		return (false);
	if (!philo->has_left_wand && take_wand(philo, philo->left_wand))
	{
		philo->has_left_wand = true;
		return (true);
	}
	else if (!philo->has_right_wand && take_wand(philo, philo->right_wand))
	{
		philo->has_right_wand = true;
		return (true);
	}
	if (philo->has_left_wand || philo->has_right_wand)
		return (true);
	else
		return (false);
}

void	release_wands(t_philo *philo)
{
	if (philo->has_left_wand)
	{
		philo->has_left_wand = false;
		philo->left_wand->rect = philo->left_wand->default_rect;
		pthread_mutex_unlock(&philo->left_wand->mutex);
	}
	if (philo->has_right_wand)
	{
		philo->has_right_wand = false;
		philo->right_wand->rect = philo->right_wand->default_rect;
		pthread_mutex_unlock(&philo->right_wand->mutex);
	}
}
