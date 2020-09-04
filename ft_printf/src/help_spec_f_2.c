/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_spec_f_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 09:06:05 by sdiego            #+#    #+#             */
/*   Updated: 2020/08/25 09:32:43 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void		float_check(t_format *f, long double num, int param)
{
	if (is_inf(num) || is_nan(num))
		no_number(f, num, param);
	else
		format_float(f, num, param);
}

long double	set_num(t_format *f, va_list *ap)
{
	long double	num;

	num = 0;
	if (f->lup == 1)
		num = (long double)va_arg(*ap, long double);
	else
		num = (long double)va_arg(*ap, double);
	return (num);
}
