/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_x.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 13:23:56 by sdiego            #+#    #+#             */
/*   Updated: 2020/08/07 18:21:51 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	no_minus_hex_help(t_format *f, char *str, int num_len, char param)
{
	char	c;

	if (f->zero && !f->precision)
		c = '0';
	else
		c = ' ';
	if (param == 'x')
		f->sym_pr += write(1, "0x", 2);
	else if (param == 'X')
		f->sym_pr += write(1, "0X", 2);
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
	f->sym_pr += write(1, str, num_len);
}

void	no_minus_hex(t_format *f, char *str, int num_len, char param)
{
	char	c;

	if (f->zero && !f->precision)
		c = '0';
	else
		c = ' ';
	if (f->hash == 2 && c == '0')
	{
		no_minus_hex_help(f, str, num_len, param);
		return ;
	}
	while (f->width-- > 0)
		f->sym_pr += write(1, &c, 1);
	if (f->hash == 2)
	{
		if (param == 'x')
			f->sym_pr += write(1, "0x", 2);
		else if (param == 'X')
			f->sym_pr += write(1, "0X", 2);
	}
	while (f->precision_num-- > 0)
		f->sym_pr += write(1, "0", 1);
	f->sym_pr += write(1, str, num_len);
}

void	minus_hex(t_format *f, char *str, int num_len, char param)
{
	if (f->hash == 2)
	{
		if (param == 'x')
			f->sym_pr += write(1, "0x", 2);
		else if (param == 'X')
			f->sym_pr += write(1, "0X", 2);
	}
	while (f->precision_num > 0)
	{
		f->sym_pr += write(1, "0", 1);
		f->precision_num--;
	}
	f->sym_pr += write(1, str, num_len);
	while (f->width > 0)
	{
		f->sym_pr += write(1, " ", 1);
		f->width--;
	}
}

void	format_hex_int(t_format *f, uintmax_t num, char param, int num_len)
{
	char	*str;

	str = NULL;
	num_len = nbr_len_unsigned(num, 16);
	if (param == 'x')
		str = ft_itoa_base_unsig(num, num_len, 16, 'a');
	else if (param == 'X')
		str = ft_itoa_base_unsig(num, num_len, 16, 'A');
	if (num == 0)
	{
		f->hash = 0;
		num_len = 1;
		if (f->precision && f->precision_num == 0)
			num_len = 0;
	}
	if (f->precision && f->precision_num > num_len)
		f->precision_num = f->precision_num - num_len;
	else
		f->precision_num = 0;
	f->width = f->width - f->precision_num - num_len - f->hash;
	if (f->minus == 0)
		no_minus_hex(f, str, num_len, param);
	if (f->minus == 1)
		minus_hex(f, str, num_len, param);
	free(str);
}

void	is_hex_int(t_format *f, va_list *ap, char param)
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
	if (f->hash == 1)
		f->hash = 2;
	format_hex_int(f, num, param, 0);
}
