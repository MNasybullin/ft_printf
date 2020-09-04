/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_lib.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 17:56:32 by sdiego            #+#    #+#             */
/*   Updated: 2020/08/08 19:31:46 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int		ft_atoi(const char *str)
{
	int	i;
	int	nbr;
	int	sign;

	i = 0;
	nbr = 0;
	sign = 1;
	while (str[i] == '\t' || str[i] == '\r' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == ' ' || str[i] == '\n')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
		nbr = (nbr * 10) + (str[i++] - '0');
	return (nbr * sign);
}

int		nbr_len_unsigned(uintmax_t nbr, int type)
{
	int	len;

	len = 0;
	if (nbr == 0)
		return (1);
	while (nbr)
	{
		nbr = nbr / type;
		len++;
	}
	return (len);
}

int		nbr_len_signed(intmax_t nbr, int type)
{
	int	len;

	len = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
	{
		len++;
		nbr = -nbr;
	}
	while (nbr)
	{
		nbr = nbr / type;
		len++;
	}
	return (len);
}

char	*ft_itoa_base(intmax_t num, int num_len, int base)
{
	char	*str;
	int		sign;
	int		rem;

	if (!(str = (char *)malloc(sizeof(char) * (num_len + 1))))
		exit(1);
	sign = 1;
	if (num < 0 && base == 10)
	{
		sign = -1;
		num = -num;
	}
	str[num_len--] = '\0';
	while (num_len != 0)
	{
		rem = num % base;
		str[num_len] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
		num_len--;
		num = num / base;
	}
	if (sign == 1)
		str[num_len] = num + '0';
	else
		str[num_len] = '-';
	return (str);
}

char	*ft_itoa_base_unsig(uintmax_t num, int num_len, int base, char param)
{
	char	*str;
	int		rem;

	if (!(str = (char *)malloc(sizeof(char) * (num_len + 1))))
		exit(1);
	str[num_len] = '\0';
	num_len--;
	while (num_len >= 0)
	{
		rem = num % base;
		if (param == 'a')
			str[num_len] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
		else if (param == 'A')
			str[num_len] = (rem > 9) ? (rem - 10) + 'A' : rem + '0';
		num_len--;
		num = num / base;
	}
	return (str);
}
