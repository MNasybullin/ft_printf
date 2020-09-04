/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 18:54:59 by sdiego            #+#    #+#             */
/*   Updated: 2020/08/25 08:14:30 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return ((char *)s);
}

int		format_pr(const char *format, va_list *ap, t_format *f, int i)
{
	while (format[i] != '\0' && i < f->flen)
	{
		if (format[i] != '%' && format[i] && i < f->flen)
			f->sym_pr += write(1, &format[i], 1);
		else if (format[i] == '%')
		{
			if (!ft_strchr(ALL, format[i + 1]))
				break ;
			while (format[++i] && ft_strchr(ALL, format[i]) && i < f->flen)
			{
				if (!ft_strchr(SPECIFIER, format[i]))
					i = modifiers(f, i, format, ap);
				else
				{
					i = specifiers(f, i, format, ap) + 1;
					init_format(f, 1);
					break ;
				}
			}
			continue;
		}
		i++;
	}
	return (f->sym_pr);
}

void	init_format(t_format *f, int param)
{
	if (param == 0)
	{
		f->sym_pr = 0;
		f->pos_i = 0;
	}
	if (param == 0 || param == 1)
	{
		f->minus = 0;
		f->plus = 0;
		f->space = 0;
		f->hash = 0;
		f->zero = 0;
		f->width = 0;
		f->precision = 0;
		f->precision_num = 0;
		f->h = 0;
		f->hh = 0;
		f->l = 0;
		f->ll = 0;
		f->lup = 0;
	}
}

int		ft_printf(const char *format, ...)
{
	int			symbols;
	va_list		ap;
	t_format	f;
	int			flen;

	init_format(&f, 0);
	flen = ft_strlen(format);
	if (!format[0] || (flen == 1 && format[0] == '%'))
		return (0);
	f.flen = flen;
	va_start(ap, format);
	symbols = format_pr(format, &ap, &f, 0);
	va_end(ap);
	return (symbols);
}
