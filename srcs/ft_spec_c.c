/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spec_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soyster <soyster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 01:18:14 by soyster           #+#    #+#             */
/*   Updated: 2020/02/04 00:02:11 by soyster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_percent(t_flag *all_mod)
{
    if (all_mod->flag_min == '-')
		write(1, "%", 1);
	if (all_mod->flag_0 == 'N' && all_mod->flag_min != '-')
	{
		while (all_mod->width != 1)
		{
			write(1, "0", 1);
			all_mod->width--;
			all_mod->result++;
		}
	}
	else
		ft_width(all_mod, 1);
	if (all_mod->flag_min != '-')
		write(1, "%", 1);
    all_mod->result = all_mod->result+ 1; // подсчет количества выведенных символов
}

int	ft_simple_width(int simple_width, int result)
{
	while (simple_width)
	{
		write(1, " ", 1);
		simple_width--;
		result++;
	}
	return (0);
}

int	ft_width(t_flag *all_mod, int len) //ширина поля
{
	if (all_mod->width != 0 && all_mod->width > len)
	{
		while (all_mod->width != len)
		{
			write(1, " ", 1);
			all_mod->width--;
			all_mod->result++;
		}
	}
	return (0);
}

int ft_spec_c(va_list all_arg, t_flag *all_mod)
{
    char    c;
    
    c = (char)va_arg(all_arg, int);
	if (all_mod->flag_min == '-') //флаг "-", вывод слева
	    ft_putchar(c);
	ft_width(all_mod, 1); //ширина поля
	if (all_mod->flag_min != '-') //нет флага "-", вывод слева
		ft_putchar(c);
    all_mod->result = all_mod->result + 1;
    return (0);
}