/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 13:03:29 by sdiego            #+#    #+#             */
/*   Updated: 2020/07/16 13:05:11 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	minus_p(t_format *f, char *str, int num_len)
{
	while (f->precision_num > 0)
	{
		f->sym_pr += write(1, "0", 1);
		f->precision_num--;
	}
	f->sym_pr += write(1, "0x", 2);
	f->sym_pr += write(1, str, num_len);
	while (f->width > 0)
	{
		f->sym_pr += write(1, " ", 1);
		f->width--;
	}
}

void	no_minus_p(t_format *f, char *str, int num_len)
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
	f->sym_pr += write(1, "0x", 2);
	while (f->precision && f->precision_num > 0)
	{
		f->sym_pr += write(1, "0", 1);
		f->precision_num--;
	}
	f->sym_pr += write(1, str, num_len);
}

void	is_pointer(t_format *f, va_list *ap)
{
	unsigned long long int	add;
	int						num_len;
	char					*str;

	add = (unsigned long long int)va_arg(*ap, void *);
	num_len = nbr_len_unsigned(add, 16);
	str = ft_itoa_base_unsig(add, num_len, 16, 'a');
	if (f->precision && add == 0 && f->precision_num == 0)
		num_len = 0;
	if (f->precision && f->precision_num > num_len)
		f->precision_num = f->precision_num - num_len;
	else
		f->precision_num = 0;
	f->width = f->width - num_len - f->precision_num - 2;
	if (f->minus == 0)
		no_minus_p(f, str, num_len);
	if (f->minus == 1)
		minus_p(f, str, num_len);
	free(str);
}
