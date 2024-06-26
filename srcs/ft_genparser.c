/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_genparser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soyster <soyster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 00:57:33 by soyster           #+#    #+#             */
/*   Updated: 2020/02/26 22:36:19 by soyster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_write_befpercent(va_list all_arg, t_flag *all_mod)
{
	while (all_mod->format[all_mod->i] && all_mod->format[all_mod->i] != '%')
	{
		write(1, &(all_mod->format[all_mod->i]), 1);
		all_mod->i++;
		all_mod->res++;
	}
	if (!all_mod->format[all_mod->i])
		return (0);
	all_mod->i++;
	return (0);
}

t_flag	*ft_fill_struct(t_flag *all_mod, const char *format, size_t len) //заполнение структуры нолями
{
	all_mod->format = (char*)malloc(len * sizeof(char));
	all_mod->format = format;
	all_mod->i = 0;
	all_mod->res = 0;
	all_mod->f_sh = '0';
	all_mod->f_0 = '0';
	all_mod->f_min = '0';
	all_mod->f_pl = '0';
	all_mod->f_sp = '0';
	all_mod->width = 0;
	all_mod->prc = -1;
	all_mod->len = 0;
	all_mod->spc = '0';
//	all_mod->f = '0';
	return (all_mod);
}

t_flag	*ft_free_allmod(t_flag *all_mod) //чистит флаги и спецификатор
{
	all_mod->f_sh = '0';
	all_mod->f_0 = '0';
	all_mod->f_min = '0';
	all_mod->f_pl = '0';
	all_mod->f_sp = '0';
	all_mod->width = 0;
	all_mod->prc = -1;
	all_mod->len = 0;
	all_mod->spc = '0';
//	all_mod->f = '0'; //??
	return (all_mod);
}

int		ft_gen_parser(va_list all_arg, const char *format) //распределяет по маленьким парсерам
{
	t_flag	*all_mod;

	all_mod = malloc(sizeof(t_flag));
	all_mod = ft_fill_struct(all_mod, format, ft_strlen(format)); //заполнение структуры нолями
	while (all_mod->format[all_mod->i] != '\0')
	{
		ft_write_befpercent(all_arg, all_mod); //печатает до процента
		if (!(all_mod->format[all_mod->i]))
			return (all_mod->res);
		ft_flags(all_arg, all_mod);
		ft_wid_and_prec(all_arg, all_mod);
		ft_length(all_arg, all_mod);
		ft_spec(all_arg, all_mod);
		ft_findfunction(all_arg, all_mod);
		ft_free_allmod(all_mod);
	}
	return (all_mod->res); //должен возвращать количество выведенных символов всеми функциями
}

int		ft_printf(const char *format, ...)
{
	va_list	all_arg; //все аргументы после строки формата
	int		result;

	if (*format == '\0') //валидация на пустой вызов функции
		return (0);
	va_start(all_arg, format);
	result = ft_gen_parser(all_arg, format);
	va_end(all_arg);
	return (result); //возвращает количество выведенных символов
}
