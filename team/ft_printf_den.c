/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_den.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soyster <soyster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 20:30:15 by fnancy            #+#    #+#             */
/*   Updated: 2019/08/06 20:37:34 by soyster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		abs(int n)
{
	if (n < 0)
		n = n * -1;
	return (n);
}

char 	*parse_flags(char *st, t_format *form)
{
	while (1)
	{
		if (*st == '-')
			form->minus = '1';
		else if (*st == '+')
			form->sign = '1';
		else if (*st == '#')
			form->sh = '1';
		else if (*st == ' ')
			form->sign = '2';
		else if (*st == '0')
			form->z_field = '1';
		else
			break ;
		st++;
	}
	return (st);
}

char 	*parse_astr(char *st, t_format *form, va_list arg)
{
	if (*st == '*' && st++)
		form->f_len = abs(va_arg(arg, int));
	else if (ft_isdigit(*st))
	{
		form->f_len = ft_atoi(st);
		while (ft_isdigit(*st))
			st++;
	}
	if (*st == '.')
	{
		form->ispre = '1';
		st++;
		if (*st == '*' && st++)
			form->f_len = abs(va_arg(arg, int));
		else if (ft_isdigit(*st))
		{
			form->f_len = ft_atoi(st);
			while (ft_isdigit(*st))
				st++;
		}
	}
	return (st);
}

static int  type_mode(char *sc)
{
	if (ft_memchr("dDioOxXuUb", (int)(*sc), 11))
		return (1);
	else if (ft_memchr("aAeEfFgG", (int)(*sc), 8))
		return (2);
	else if (*sc == 's')
		return (3);
	else if (*sc == 'c')
		return (4);
	else if (*sc == 'p')
		return (5);
	else if (*sc == '%')
	{
		return (6);
	}
	return (0);
}

static char *type_parser(char *sc, t_format *f)
{
	long double m;
	f->size = 4;
	while (!(f->type = type_mode(sc)))
	{
		!(ft_strncmp("hh", sc, 2)) && f->size < (int)sizeof(long)\
        ? f->size = sizeof(char) : 0;
		*sc == 'h' && f->size < (int)8 && f->size > (int)sizeof(char)\
        ? f->size = sizeof(short) : 0;
		*sc == 'l' && f->size < (int)sizeof(m) ? f->size = sizeof(long) : 0;
		!(ft_strncmp("ll", sc, 2)) && f->size < (int)sizeof(m) \
        ? f->size = sizeof(long long) : 0;
		*sc == 'z' && f->size < (int)sizeof(m) ? f->size = sizeof(size_t) : 0;
		*sc == 't' && f->size < (int)sizeof(m) ? f->size = sizeof(size_t) : 0;
		*sc == 'j' && f->size < (int)sizeof(m) ? f->size = sizeof(size_t) : 0;
		*sc == 'L' ? f->size = sizeof(m) : 0;
		++sc;
	}
	f->type == 1 && f->size > 8 ? f->size = 8 : 0;
	f->type == 2 && !f->size ? f->size = 8 : 0;
	f->type == 2 && f->size < 8 ? f->size = 8 : 0;
	f->type == 3 || f->type == 5 ? f->size = 8 : 0;
	f->type == 4 ? f->size = 1 : 0;
	++sc;
	return (sc);
}

char 	*format_parser(char *st, t_format *form, va_list arg)
{
	ft_bzero(form, sizeof(t_format));
	st = parse_flags(st, form);
	st = parse_astr(st, form, arg);
	st = type_parser(st, form);
	form->spec = *(st - 1);
	return (st);
}

void	ft_putchar_n(char ch, int n)
{
	while (n > 0)
	{
		write(1, &ch, 1);
		n--;
	}
}

int		paste_real_str(int size, char *str, t_format *form, int len)
{
	if (form->minus == '1')
	{
		ft_putchar_n((form->z_field == '1') ? '0' : ' ',
				(form->pre > len || form->ispre == '0') ? size - len : size
						- form->pre);
		write(1, str, (form->ispre == '1' && form->pre < len) ? form->pre : len);
	}
	else
	{
		write(1, str, (form->ispre == '1' && form->pre < len) ? form->pre : len);
		ft_putchar_n((form->z_field == '1') ? '0' : ' ',
				(form->pre > len || form->ispre == '0') ? size - len : size
						- form->pre);
	}
	if (size >= len)
		return (size);
	else if (form->pre == 0 || len < form->pre)
		return (len);
	else
		return (form->pre);
}

int 	paste_str(t_format *form, va_list arg)
{
	char	*str;
	int 	len;
	int 	size;

	str = va_arg(arg, char *);
	size = form->f_len;
	if (form->ispre == '1' && form->pre == 0)
	{
		ft_putchar_n(' ', form->f_len);
		return (size);
	}
	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	return (paste_real_str(size, str, form, len));
}

size_t insert_spec(t_format *form, va_list arg)
{
	if (form->spec == 's')
		return (paste_str(form, arg));
	return (0);
}

int 	ft_printf(const char *str, ...)
{
	va_list arg;
	size_t ar[2];
	char *inp[2];
	t_format form;
	int i;

	va_start(arg, str);
	inp[0] = (char *)str;
	ar[1] = 0;
	while ((inp[1] = ft_strchr(inp[0], '%')))
	{
		write(1, inp[0], (ar[0] = inp[1] - inp[0]));
		ar[1] += ar[0];
		if (*(inp[1]) == '%' && ++inp[1])
		{
			inp[1] = format_parser(inp[1], &form, arg);
			ar[1] += insert_spec(&form, arg);
		}
		inp[0] = inp[1];
	}
	ar[0] = ft_strlen(inp[0]);
	write(1, inp[0], ar[0]);
	va_end(arg);
	return ((int)(ar[1] + ar[0]));
}