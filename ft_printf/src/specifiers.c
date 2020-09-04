/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifiers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 19:06:55 by sdiego            #+#    #+#             */
/*   Updated: 2020/08/07 19:13:22 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	width_asterisk(t_format *f, const char *format, va_list *ap)
{
	if (format[f->pos_i] == '*')
	{
		f->width = va_arg(*ap, int);
		if (f->width < 0)
		{
			f->minus = 1;
			f->width = -(f->width);
		}
		while (format[f->pos_i] == '*')
			f->pos_i++;
	}
}

int		precision_asterisk(t_format *f, const char *format, va_list *ap, int i)
{
	int	number;

	number = 0;
	if (format[i] == '*')
	{
		number = va_arg(*ap, int);
		if (number < 0)
			f->precision = 0;
		else
			f->precision_num = number;
		while (format[i] == '*')
			i++;
	}
	return (i);
}

void	is_char(t_format *f, va_list *ap)
{
	unsigned char	num;
	char			c;

	num = (unsigned char)va_arg(*ap, int);
	if (f->zero)
		c = '0';
	else
		c = ' ';
	f->width--;
	if (f->minus == 0)
	{
		while (f->width-- > 0)
			f->sym_pr += write(1, &c, 1);
		f->sym_pr += write(1, &num, 1);
	}
	else if (f->minus == 1)
	{
		f->sym_pr += write(1, &num, 1);
		while (f->width-- > 0)
			f->sym_pr += write(1, &c, 1);
	}
}

void	is_percent(t_format *f)
{
	char	c;

	if (f->zero)
		c = '0';
	else
		c = ' ';
	f->width--;
	if (f->width && f->minus == 1)
	{
		f->sym_pr += write(1, "%", 1);
		while (f->width-- > 0)
			f->sym_pr += write(1, &c, 1);
	}
	else if (f->width && f->minus == 0)
	{
		while (f->width-- > 0)
			f->sym_pr += write(1, &c, 1);
		f->sym_pr += write(1, "%", 1);
	}
	else
		f->sym_pr += write(1, "%", 1);
}

int		specifiers(t_format *f, int i, const char *format, va_list *ap)
{
	f->pos_i = i;
	if (format[i] == 'd' || format[i] == 'i')
		is_int(f, ap, 0, 0);
	else if (format[i] == 'o')
		is_octal(f, ap);
	else if (format[i] == 'u')
		is_unsigned_int(f, ap);
	else if (format[i] == 'x' || format[i] == 'X')
		is_hex_int(f, ap, format[i]);
	else if (format[i] == 'f')
		is_float(f, ap);
	else if (format[i] == 'c')
		is_char(f, ap);
	else if (format[i] == 's')
		is_string(f, ap);
	else if (format[i] == 'p')
		is_pointer(f, ap);
	else if (format[i] == '%')
		is_percent(f);
	return (f->pos_i);
}
