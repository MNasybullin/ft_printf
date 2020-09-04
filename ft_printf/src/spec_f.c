/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 16:19:36 by sdiego            #+#    #+#             */
/*   Updated: 2020/08/25 09:06:20 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	no_minus_float_help(t_format *f, t_spec *h, char param_c, char c)
{
	if (f->width > 0 && c == '0')
	{
		if (f->space)
		{
			f->sym_pr += write(1, " ", 1);
			f->space = 0;
		}
		if (param_c != '0')
			f->sym_pr += write(1, &param_c, 1);
		h->param = 0;
	}
}

void	no_minus_float(t_format *f, char *str, t_spec *h)
{
	char	c;
	char	param_c;

	if (f->zero)
		c = '0';
	else
		c = ' ';
	param_c = '0';
	if (h->param == 1)
		param_c = '+';
	else if (h->param == -1)
		param_c = '-';
	no_minus_float_help(f, h, param_c, c);
	while (f->width-- > 0)
		f->sym_pr += write(1, &c, 1);
	if (f->space == 1)
		f->sym_pr += write(1, " ", 1);
	if (h->param != 0 && param_c != '0')
		f->sym_pr += write(1, &param_c, 1);
	f->sym_pr += write(1, str, h->str_len);
	if (f->hash == 1)
		f->sym_pr += write(1, ".", 1);
}

void	minus_float(t_format *f, char *str, t_spec *h)
{
	if (f->space)
		f->sym_pr += write(1, " ", 1);
	if (h->param == 1)
		f->sym_pr += write(1, "+", 1);
	else if (h->param == -1)
		f->sym_pr += write(1, "-", 1);
	f->sym_pr += write(1, str, h->str_len);
	if (f->hash == 1)
		f->sym_pr += write(1, ".", 1);
	while (f->width > 0)
	{
		f->sym_pr += write(1, " ", 1);
		f->width--;
	}
}

void	format_float(t_format *f, long double num, int param)
{
	char	*str;
	t_spec	h;

	h.dot = 0;
	h.param = param;
	if (f->precision == 0)
		f->precision_num = 6;
	h.num = num;
	h.defn = num;
	str = double_to_str(f->precision_num, &h, 0, 0);
	if (!(h.dot == 0 && f->hash == 1))
		f->hash = 0;
	if (param != 0)
		f->width = f->width - (h.str_len + f->space + 1 + f->hash);
	else
		f->width = f->width - (h.str_len + f->space + f->hash);
	if (f->minus == 0)
		no_minus_float(f, str, &h);
	if (f->minus == 1)
		minus_float(f, str, &h);
	free(str);
}

void	is_float(t_format *f, va_list *ap)
{
	int			param;
	long double	num;
	int			bit;

	bit = 0;
	param = 0;
	num = set_num(f, ap);
	ft_bits(num, &bit);
	if (num < 0)
	{
		param = -1;
		f->space = 0;
		num = num * -1;
	}
	if (f->plus == 1 && param != -1)
		param = 1;
	if (bit == 1 && num == 0)
	{
		param = -1;
		f->space = 0;
		num = num * -1;
	}
	if (f->plus == 1 && bit == 0 && num == 0)
		param = 1;
	float_check(f, num, param);
}
