/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_array_del.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 12:06:45 by ashih             #+#    #+#             */
/*   Updated: 2017/12/29 12:09:45 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_char_array_del(char **array)
{
	int		i;

	if (!array)
		return ;
	i = 0;
	while (array[i] != 0)
		ft_strdel(array + i++);
	ft_memdel((void **)&array);
}
