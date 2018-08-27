/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 15:25:04 by ashih             #+#    #+#             */
/*   Updated: 2018/08/22 18:02:19 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

SDL_Texture		*load_tex(char *filename, t_master *m)
{
	char		*full_path;
	SDL_Texture *tex;

	full_path = ft_strjoin(m->path, filename);
	if (full_path)
	{
		tex = IMG_LoadTexture(m->ren, full_path);
		ft_strdel(&full_path);
		return (tex);
	}
	else
		return (NULL);
}

void			render_tex(SDL_Texture *tex, SDL_Rect *rect, SDL_Renderer *ren)
{
	SDL_RenderCopy(ren, tex, NULL, rect);
}
