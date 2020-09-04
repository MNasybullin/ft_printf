/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_spec_f.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 20:04:05 by sdiego            #+#    #+#             */
/*   Updated: 2020/08/25 09:29:27 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int		is_nan(long double num)
{
	return (!(num == num));
}

int		is_inf(long double num)
{
	long double	inf;

	inf = 1.0 / 0.0;
	return (num == inf);
}

void	no_number_format(t_format *f, char *str, t_spec *h)
{
	if (f->minus == 0)
		no_minus_float(f, str, h);
	if (f->minus == 1)
		minus_float(f, str, h);
	free(str);
}

void	no_number(t_format *f, long double num, int param)
{
	char	*str;
	t_spec	h;

	h.param = param;
	h.str_len = 3;
	if (!(str = (char *)malloc(sizeof(char) * 3)))
		exit(1);
	if (is_inf(num))
	{
		str[0] = 'i';
		str[1] = 'n';
		str[2] = 'f';
	}
	else if (is_nan(num))
	{
		str[0] = 'n';
		str[1] = 'a';
		str[2] = 'n';
	}
	if (param != 0)
		f->width = f->width - (h.str_len + f->space + 1);
	else
		f->width = f->width - (h.str_len + f->space);
	no_number_format(f, str, &h);
}

void	ft_bits(double num, int *bits)
{
	unsigned char	*px;
	unsigned char	cx;
	int				j;
	unsigned long	i;

	px = (unsigned char *)(&num);
	i = 0;
	while (i < sizeof(num))
	{
		cx = *(px + i);
		j = 0;
		while (j < 8)
		{
			*bits += (cx >> j) & 1;
			j++;
		}
		i++;
	}
}
