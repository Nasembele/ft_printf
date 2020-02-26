/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spec_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soyster <soyster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 01:18:14 by soyster           #+#    #+#             */
/*   Updated: 2020/02/25 12:37:01 by mleticia         ###   ########.fr       */
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

	if (all_mod->prc == 0 && !all_mod->width) // ?!?!
		return (0);				 //?!?!			
	if (all_mod->prc == 0 && all_mod->width)
	{
		ft_simple_width(all_mod->width, all_mod->res);
		return (0);
	}
	if (all_mod->prc > 0 && all_mod->prc < len)
		len_prec = all_mod->prc;
	else
		len_prec = len;
	if (all_mod->f_min == '-')
		ft_putstr_len(str, len_prec);
	ft_width(all_mod, len_prec);
	if (all_mod->f_min != '-')
		ft_putstr_len(str, len_prec);
	all_mod->res = all_mod->res + len; // результат сделать
	return (0);
}