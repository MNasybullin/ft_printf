/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 12:50:07 by sdiego            #+#    #+#             */
/*   Updated: 2020/08/25 08:42:40 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	no_minus_string(t_format *f, char *str, size_t len, char c)
{
	while (f->width > (int)len)
	{
		f->sym_pr += write(1, &c, 1);
		f->width--;
	}
	f->sym_pr += write(1, str, len);
}

void	minus_string(t_format *f, char *str, size_t len)
{
	f->sym_pr += write(1, str, len);
	while (f->width - (int)len > 0)
	{
		f->sym_pr += write(1, " ", 1);
		f->width--;
	}
}

void	is_string(t_format *f, va_list *ap)
{
	char	*str;
	size_t	len;
	char	c;

	str = NULL;
	str = (char *)va_arg(*ap, char *);
	if (str == NULL)
		str = "(null)";
	len = ft_strlen(str);
	if (f->zero)
		c = '0';
	else
		c = ' ';
	if (f->precision && (int)len > f->precision_num)
		len = f->precision_num;
	if (f->minus == 0)
		no_minus_string(f, str, len, c);
	else if (f->minus == 1)
		minus_string(f, str, len);
}
