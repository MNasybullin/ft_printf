/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_octal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 13:52:18 by sdiego            #+#    #+#             */
/*   Updated: 2020/05/17 13:52:18 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	no_minus_octal(t_format *f, char *str, int num_len)
{
	char	c;

	if (f->zero && !f->precision)
		c = '0';
	else
		c = ' ';
	while (f->width > 0)
	{
		f->sym_pr += write(1, &c, 1);
		f->width--;
	}
	while (f->precision_num > 0)
	{
		f->sym_pr += write(1, "0", 1);
		f->precision_num--;
	}
	if (f->hash == 1)
		f->sym_pr += write(1, "0", 1);
	f->sym_pr += write(1, str, num_len);
}

void	minus_octal(t_format *f, char *str, int num_len)
{
	while (f->precision_num > 0)
	{
		f->sym_pr += write(1, "0", 1);
		f->precision_num--;
	}
	if (f->hash == 1)
		f->sym_pr += write(1, "0", 1);
	f->sym_pr += write(1, str, num_len);
	while (f->width > 0)
	{
		f->sym_pr += write(1, " ", 1);
		f->width--;
	}
}

void	format_octal(t_format *f, uintmax_t num)
{
	int		num_len;
	char	*str;

	num_len = nbr_len_unsigned(num, 8);
	str = ft_itoa_base_unsig(num, num_len, 8, 'a');
	if (num == 0)
	{
		if (f->hash == 1)
			num_len = 0;
		if (f->precision && f->precision_num == 0)
			num_len = 0;
	}
	if (f->precision && f->precision_num > num_len)
		f->precision_num = f->precision_num - num_len - f->hash;
	else
		f->precision_num = 0;
	f->width = f->width - f->precision_num - num_len - f->hash;
	if (f->minus == 0)
		no_minus_octal(f, str, num_len);
	if (f->minus == 1)
		minus_octal(f, str, num_len);
	free(str);
}

void	is_octal(t_format *f, va_list *ap)
{
	uintmax_t	num;

	if (f->hh == 1)
		num = (unsigned char)va_arg(*ap, unsigned int);
	else if (f->h == 1)
		num = (unsigned short int)va_arg(*ap, unsigned int);
	else if (f->l == 1)
		num = (unsigned long int)va_arg(*ap, unsigned long int);
	else if (f->ll == 1)
		num = (unsigned long long int)va_arg(*ap, unsigned long long int);
	else
		num = (unsigned int)va_arg(*ap, unsigned int);
	format_octal(f, num);
}
