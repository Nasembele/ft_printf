/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spec_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soyster <soyster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 01:18:14 by soyster           #+#    #+#             */
/*   Updated: 2020/02/03 23:29:49 by soyster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_putstr_len(char const *s, size_t len)
{
	size_t i;

	if (s)
	{
		i = 0;
		while (i != len)
		{
			ft_putchar(s[i]);
			i++;
		}
	}
	return ;
}

int ft_spec_s(va_list all_arg, t_flag *all_mod)
{
	char*	str;
	int		len;
	int		len_prec;

	
	str = (char*)va_arg(all_arg, char*);
	if (str == NULL) // зафришить старую строку
	{
		str = (char*)malloc(sizeof(char) * 6);
		str[0] = '('; ///111
		str[1] = 'n'; ///111
		str[2] = 'u'; ///111
		str[3] = 'l'; ///111
		str[4] = 'l'; ///111
		str[5] = ')'; ///111
	}
	len = ft_strlen(str);

	if (all_mod->precision == 0 && !all_mod->width) // ?!?!
		return (0);				 //?!?!			
	if (all_mod->precision == 0 && all_mod->width)
	{
		ft_simple_width(all_mod->width, all_mod->result);
		return (0);
	}
	if (all_mod->precision > 0 && all_mod->precision < len)
		len_prec = all_mod->precision;
	else
		len_prec = len;
	if (all_mod->flag_min == '-')
		ft_putstr_len(str, len_prec);
	ft_width(all_mod, len_prec);
	if (all_mod->flag_min != '-')
		ft_putstr_len(str, len_prec);
	all_mod->result = all_mod->result + len; // результат сделать
	return (0);
}