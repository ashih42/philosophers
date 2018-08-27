/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 14:03:29 by ashih             #+#    #+#             */
/*   Updated: 2018/08/23 09:43:06 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			check_for_tags(const char **format, int *chars_printed)
{
	if (apply_a_style(format))
		return (1);
	else if (print_an_emoji(format))
		return (1);
	else
	{
		ft_putchar(*(*format)++);
		(*chars_printed)++;
		return (0);
	}
}

int			parse_one_term(const char **format, va_list *args,
		int *chars_printed)
{
	int		flags[NUM_FLAGS];

	ft_bzero(flags, sizeof(flags));
	while (**format)
	{
		if (set_precision(format, args, flags))
			;
		else if (set_width(format, args, flags))
			;
		else if (set_a_double_flag(format, flags))
			;
		else if (set_a_single_flag(format, flags))
			;
		else if (do_an_ident(format, args, flags, chars_printed))
			return (1);
		else
		{
			ft_printf_any_char(*(*format)++, flags, chars_printed);
			return (0);
		}
	}
	return (-1);
}

static void	putchar_inc(char **format, int *chars_printed)
{
	ft_putchar(**format);
	(*format)++;
	(*chars_printed)++;
}

int			ft_printf(const char *format, ...)
{
	static pthread_mutex_t	g_printf_mutex = PTHREAD_MUTEX_INITIALIZER;
	va_list					args;
	int						chars_printed;

	pthread_mutex_lock(&g_printf_mutex);
	va_start(args, format);
	chars_printed = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (parse_one_term(&format, &args, &chars_printed) == -1)
				return (chars_printed);
		}
		else if (*format == '{')
			check_for_tags(&format, &chars_printed);
		else
			putchar_inc((char **)&format, &chars_printed);
	}
	va_end(args);
	pthread_mutex_unlock(&g_printf_mutex);
	return (chars_printed);
}
