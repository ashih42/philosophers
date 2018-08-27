/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 10:44:22 by ashih             #+#    #+#             */
/*   Updated: 2018/08/23 11:14:04 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void			play_sound(char *filename, char *path)
{
	char		*str;
	char		*temp;

	str = ft_strjoin(path, filename);
	temp = str;
	str = ft_strjoin("afplay ", str);
	ft_strdel(&temp);
	temp = str;
	str = ft_strjoin(str, " &");
	ft_strdel(&temp);
	system(str);
	ft_strdel(&str);
}
