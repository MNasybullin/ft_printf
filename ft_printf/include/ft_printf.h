/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 17:57:45 by sdiego            #+#    #+#             */
/*   Updated: 2020/09/07 16:57:40 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# define ALL "-+ #0123456789*.hlLdiouxXfcsp%"
# define SPECIFIER "diouxXfcsp%"
# define FLAGS "-+ #0"
# define LENGTHS "hlL"

typedef struct		s_spec
{
	int				str_len;
	int				dot;
	int				param;
	long double		num;
	long double		defn;
}					t_spec;

typedef struct		s_format
{
	int				flen;
	int				sym_pr;
	int				pos_i;

	int				minus;
	int				plus;
	int				space;
	int				hash;
	int				zero;

	int				width;

	int				precision;
	int				precision_num;

	int				h;
	int				hh;
	int				l;
	int				ll;
	int				lup;
}					t_format;

/*
** mini lib
*/
char				*ft_strchr(const char *s, int c);
int					ft_atoi(const char *str);
int					nbr_len_signed(intmax_t nbr, int type);
char				*ft_itoa_base(intmax_t num, int num_len, int base);
int					nbr_len_unsigned(uintmax_t nbr, int type);
char				*ft_itoa_base_unsig(uintmax_t num, int num_len,
int base, char param);
size_t				ft_strlen(const char *s);
char				*double_to_str(int tolerance, t_spec *h, int j, int param);

int					modifiers(t_format *f, int i, const char *format,
va_list *ap);
int					specifiers(t_format *f, int i, const char *format,
va_list *ap);
void				init_format(t_format *f, int param);
void				is_int(t_format *f, va_list *ap, int param,
long long int num);
void				is_octal(t_format *f, va_list *ap);
void				is_unsigned_int(t_format *f, va_list *ap);
void				is_hex_int(t_format *f, va_list *ap, char param);
void				is_float(t_format *f, va_list *ap);
void				is_string(t_format *f, va_list *ap);
void				is_pointer(t_format *f, va_list *ap);
void				width_asterisk(t_format *f, const char *format,
va_list *ap);
int					precision_asterisk(t_format *f, const char *format,
va_list *ap, int i);
int					ft_printf(const char *format, ...);
void				ft_bits(double num, int *bits);
void				no_number(t_format *f, long double num, int param);
int					is_inf(long double num);
int					is_nan(long double num);
void				no_minus_float(t_format *f, char *str, t_spec *h);
void				minus_float(t_format *f, char *str, t_spec *h);
long double			set_num(t_format *f, va_list *ap);
void				format_float(t_format *f, long double num, int param);
void				float_check(t_format *f, long double num, int param);

#endif
