/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spec_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soyster <soyster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 01:18:14 by soyster           #+#    #+#             */
/*   Updated: 2020/02/16 21:47:03 by soyster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

#include "float.h"

int		ft_rounding(t_flag *all_mod)
{
	int a;
	
	//a = all_mod->fractional[all_mod->index];
	//all_mod->index--;
	all_mod->fractional[all_mod->index] = all_mod->fractional[all_mod->index] + 1;
	if (all_mod->fractional[all_mod->index] == 10)
	{
		all_mod->fractional[all_mod->index] = 0;
		all_mod->index--;
		if (all_mod->index != -1)
			ft_rounding(all_mod);
		else
			return (1);
	}
	else
		return (0);
	if (all_mod->index == -1)
		return (1);
	else
		return (0);
}

void	ft_spec_f(va_list all_arg, t_flag *all_mod)
{
	long double f;
	long		num_start;
	long double	num_end;
	int			digit;
	//int		*fractional;
	//int			index;
	//char		digit;
	int			k;
	int			check_sign;

	check_sign = 0;	
	k = 0;
	if (all_mod->length == 5)
		f = va_arg(all_arg, long double);
	else
		f = va_arg(all_arg, double);
	num_start = (long)f;
	//ft_printf("%ld", num_start);
	//write(1, ".", 1);
	if (num_start < 0)
	{
		f = f * -1;
		num_start = num_start * -1;
		check_sign = 1;
	}
	num_end = f - num_start;
	if (num_end < 0)
	{
		check_sign = 1;
		num_end = num_end * (-1);
	}
	all_mod->index = 0;
	if (all_mod->precision == -1)
		all_mod->precision = 6;
	all_mod->fractional = (int*)malloc(all_mod->precision * sizeof(int));
	while (all_mod->index < all_mod->precision)
	{
		//digit = (int)(num_end * 10);
		all_mod->fractional[all_mod->index] = (int)(num_end * 10);
		//fractional[index] = 1;
		//ft_printf("%i", fractional[index]); //поменять на наш printf
		num_end = (num_end) * 10 - all_mod->fractional[all_mod->index];
		all_mod->index++;
	}
	//index--;
	if ((int)(num_end * 10) > 4)
	{
		all_mod->index--;
		if (ft_rounding(all_mod))
			num_start = num_start + 1;
	}
	if (check_sign == 1)
		write(1, "-", 1);
	//if (all_mod->precision == 0)
	//{
	//	if ((int)(num_end * 10) > 4)
	//		num_start = num_start + 1;
	//
	//}
	ft_printf("%ld", num_start);
	if (all_mod->precision != 0)
		write(1, ".", 1);	
	while (k < all_mod->precision)
	{
		ft_printf("%i", all_mod->fractional[k]);
		k++;
	}
	
	//printf("%", fractional);
	//printf("%i", LDBL_DIG); // количество заничмых чисел
}