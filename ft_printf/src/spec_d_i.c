/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_d_i.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 12:45:54 by sdiego            #+#    #+#             */
/*   Updated: 2020/07/16 13:17:01 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	no_minus_int_help(t_format *f, char *str, int num_len, int param)
{
	char	c;
	char	param_c;

	if (f->zero && !f->precision)
		c = '0';
	else
		c = ' ';
	param_c = '0';
	if (param == 1)
		param_c = '+';
	else if (param == -1)
		param_c = '-';
	while (f->width-- > 0)
	{
		f->sym_pr += write(1, &c, 1);
	}
	if (f->space == 1)
		f->sym_pr += write(1, " ", 1);
	if (param != 0 && param_c != '0')
		f->sym_pr += write(1, &param_c, 1);
	while (f->precision_num-- > 0)
	{
		f->sym_pr += write(1, "0", 1);
	}
	f->sym_pr += write(1, str, num_len);
}

void	no_minus_int(t_format *f, char *str, int num_len, int param)
{
	char	c;
	char	param_c;

	if (f->zero && !f->precision)
		c = '0';
	else
		c = ' ';
	param_c = '0';
	if (param == 1)
		param_c = '+';
	else if (param == -1)
		param_c = '-';
	if (f->width > 0 && c == '0')
	{
		if (f->space)
		{
			f->sym_pr += write(1, " ", 1);
			f->space = 0;
		}
		if (param_c != '0')
			f->sym_pr += write(1, &param_c, 1);
		param = 0;
	}
	no_minus_int_help(f, str, num_len, param);
}

void	minus_int(t_format *f, char *str, int num_len, int param)
{
	if (f->space)
		f->sym_pr += write(1, " ", 1);
	if (param == 1)
		f->sym_pr += write(1, "+", 1);
	else if (param == -1)
		f->sym_pr += write(1, "-", 1);
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

void	format_int(t_format *f, intmax_t num, int param)
{
	int		num_len;
	char	*str;

	num_len = nbr_len_signed(num, 10);
	str = ft_itoa_base(num, num_len, 10);
	if (f->precision && num == 0 && f->precision_num == 0)
		num_len = 0;
	if (f->precision && f->precision_num > num_len)
		f->precision_num = f->precision_num - num_len;
	else
		f->precision_num = 0;
	if (param != 0)
		f->width = f->width - (f->precision_num + num_len + f->space + 1);
	else
		f->width = f->width - (f->precision_num + num_len + f->space);
	if (f->minus == 0)
		no_minus_int(f, str, num_len, param);
	if (f->minus == 1)
		minus_int(f, str, num_len, param);
	free(str);
}

void	is_int(t_format *f, va_list *ap, int param, long long int num)
{
	if (f->h == 1)
		num = (short int)va_arg(*ap, int);
	else if (f->hh == 1)
		num = (signed char)va_arg(*ap, int);
	else if (f->l == 1)
		num = (long int)va_arg(*ap, long int);
	else if (f->ll == 1)
		num = (long long int)va_arg(*ap, long long int);
	else
		num = (int)va_arg(*ap, int);
	if (f->plus == 1 && num >= 0)
		param = 1;
	else if (num < 0)
	{
		param = -1;
		f->space = 0;
		num = num * -1;
	}
	if (num == LLONG_MIN)
	{
		f->sym_pr += write(1, "-9223372036854775808", 20);
		return ;
	}
	format_int(f, num, param);
}
