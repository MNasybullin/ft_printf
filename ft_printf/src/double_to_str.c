/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_to_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 16:26:12 by sdiego            #+#    #+#             */
/*   Updated: 2020/08/25 10:04:13 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	rounding_a_number(int *i, int *j, char *s, int *param)
{
	*i = *j;
	*j = *j - 1;
	while ((s[*j] == '9' || s[*j] == '.') && *j >= 0)
	{
		if (s[*j] == '9')
			s[*j] = '0';
		*j = *j - 1;
	}
	if (*j < 0)
		*param = 1;
	else
		s[*j] = s[*j] + (int)1;
	*j = *i;
}

int		count_after_dot(t_spec *h, int i)
{
	while ((long long int)h->num > 0)
	{
		h->num = h->num / 10;
		i = i + 1;
	}
	h->num = h->num * 10;
	return (i);
}

void	push_to_str(t_spec *h, int *i, int *j, char *s)
{
	int		tolerance;

	tolerance = *i;
	if ((int)h->num == 0)
		*i = *i + 1;
	else
	{
		*i = count_after_dot(h, *i);
	}
	while (*i > 0)
	{
		s[*j] = (int)h->num + '0';
		*i = *i - 1;
		*j = *j + 1;
		if (*i == tolerance && tolerance != 0)
		{
			s[*j] = '.';
			h->dot = 1;
			*j = *j + 1;
		}
		h->num = h->num - (int)h->num;
		h->num = h->num * 10;
	}
}

char	*str_malloc(void)
{
	char	*s;

	if (!(s = (char *)malloc(sizeof(char) * 150)))
	{
		exit(1);
	}
	return (s);
}

/*
** take a positive number
*/

char	*double_to_str(int tolerance, t_spec *h, int j, int param)
{
	char	*s;
	char	*temp;
	int		i;

	i = tolerance;
	s = str_malloc();
	push_to_str(h, &i, &j, s);
	if ((int)h->num >= 5 && !(h->defn == 0.5
	|| h->defn == 2.5 || h->defn == 4.5))
		rounding_a_number(&i, &j, s, &param);
	s[j] = '\0';
	j++;
	if (!(temp = (char *)malloc(sizeof(char) * (j - 1 + param))))
		exit(1);
	h->str_len = j - 1 + param;
	i = 0;
	if (param == 1)
		temp[i] = 1 + '0';
	while (i < j)
	{
		temp[i + param] = s[i];
		i++;
	}
	free(s);
	return (temp);
}
