/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifiers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 18:56:01 by sdiego            #+#    #+#             */
/*   Updated: 2020/07/16 15:22:50 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	flag(t_format *f, const char *format)
{
	while (ft_strchr(FLAGS, format[f->pos_i]))
	{
		if (format[f->pos_i] == '-')
			f->minus = 1;
		if (format[f->pos_i] == '+')
			f->plus = 1;
		if (format[f->pos_i] == ' ')
			f->space = 1;
		if (format[f->pos_i] == '#')
			f->hash = 1;
		if (format[f->pos_i] == '0')
			f->zero = 1;
		f->pos_i++;
	}
	if (f->plus == 1)
		f->space = 0;
	if (f->minus == 1)
		f->zero = 0;
}

void	width(t_format *f, const char *format, va_list *ap)
{
	width_asterisk(f, format, ap);
	if (format[f->pos_i] >= '0' && format[f->pos_i] <= '9')
	{
		f->width = ft_atoi(&format[f->pos_i]);
		while (format[f->pos_i] >= '0' && format[f->pos_i] <= '9')
		{
			f->pos_i++;
			if (format[f->pos_i] == '*')
			{
				if (f->width < 0)
				{
					f->minus = 1;
					f->width = -(f->width);
				}
				while (format[f->pos_i] == '*')
					f->pos_i++;
			}
		}
	}
}

void	precision(t_format *f, const char *format, va_list *ap)
{
	int	i;

	i = f->pos_i;
	if (format[i] == '.')
	{
		f->precision = 1;
		i++;
		if (format[i] >= '0' && format[i] <= '9')
		{
			f->precision_num = ft_atoi(&format[i]);
			while (format[i] >= '0' && format[i] <= '9')
				i++;
		}
		else
			i = precision_asterisk(f, format, ap, i);
	}
	f->pos_i = i;
}

void	length(t_format *f, const char *format)
{
	if (ft_strchr(LENGTHS, format[f->pos_i]))
	{
		if (format[f->pos_i] == 'h')
		{
			if (format[f->pos_i + 1] == 'h')
			{
				f->hh = 1;
			}
			else
				f->h = 1;
		}
		if (format[f->pos_i] == 'l')
		{
			if (format[f->pos_i + 1] == 'l')
			{
				f->ll = 1;
			}
			else
				f->l = 1;
		}
		if (format[f->pos_i] == 'L')
			f->lup = 1;
	}
	while (ft_strchr(LENGTHS, format[f->pos_i]))
		f->pos_i++;
}

int		modifiers(t_format *f, int i, const char *format, va_list *ap)
{
	f->pos_i = i;
	flag(f, format);
	width(f, format, ap);
	precision(f, format, ap);
	length(f, format);
	return (f->pos_i - 1);
}
