/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_u.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 17:18:15 by sdiego            #+#    #+#             */
/*   Updated: 2020/05/19 17:18:15 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	no_minus_u_int(t_format *f, char *str, int num_len)
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
	f->sym_pr += write(1, str, num_len);
}

void	minus_u_int(t_format *f, char *str, int num_len)
{
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

void	format_unsigned_int(t_format *f, uintmax_t num)
{
	int		num_len;
	char	*str;

	num_len = nbr_len_unsigned(num, 10);
	str = ft_itoa_base_unsig(num, num_len, 10, 'a');
	if (f->precision && num == 0 && f->precision_num == 0)
		num_len = 0;
	if (f->precision && f->precision_num > num_len)
		f->precision_num = f->precision_num - num_len;
	else
		f->precision_num = 0;
	f->width = f->width - f->precision_num - num_len;
	if (f->minus == 0)
		no_minus_u_int(f, str, num_len);
	if (f->minus == 1)
		minus_u_int(f, str, num_len);
	free(str);
}

void	is_unsigned_int(t_format *f, va_list *ap)
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
	format_unsigned_int(f, num);
}
