/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 17:59:17 by ashih             #+#    #+#             */
/*   Updated: 2018/08/26 21:56:49 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

char			*uint32_to_str(uint32_t num)
{
	char		*str;
	int			i;

	if (!(str = ft_strnew(10)))
		return (NULL);
	if (num == 0)
		ft_strcpy(str, "0");
	else
	{
		i = 0;
		while (num != 0)
		{
			str[i++] = '0' + (num % 10);
			num /= 10;
		}
	}
	ft_strrev(str);
	return (str);
}

int				render_num(uint32_t num, SDL_Color color, SDL_Rect rect,
	t_master *m)
{
	char		*str;
	int			ret;

	if (!(str = uint32_to_str(num)))
		return (-1);
	ret = render_str(str, color, rect, m);
	ft_strdel(&str);
	return (ret);
}

int				render_str(char *message, SDL_Color color, SDL_Rect rect,
	t_master *m)
{
	SDL_Surface	*surf;
	SDL_Texture *tex;

	if (!(surf = TTF_RenderText_Blended(m->font, message, color)) ||
		!(tex = SDL_CreateTextureFromSurface(m->ren, surf)))
		return (ft_puterror(ERROR_MEMORY, 0, -1));
	SDL_QueryTexture(tex, NULL, NULL, &rect.w, &rect.h);
	render_tex(tex, &rect, m->ren);
	SDL_DestroyTexture(tex);
	SDL_FreeSurface(surf);
	return (0);
}

TTF_Font		*load_font(char *filename, t_master *m, int size)
{
	char		*full_path;
	TTF_Font	*font;

	full_path = ft_strjoin(m->path, filename);
	if (full_path)
	{
		font = TTF_OpenFont(full_path, size);
		ft_strdel(&full_path);
		return (font);
	}
	else
		return (NULL);
}
