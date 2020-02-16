/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spec_f_old.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soyster <soyster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 01:18:14 by soyster           #+#    #+#             */
/*   Updated: 2020/02/15 21:43:20 by soyster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_spec_f(va_list all_arg, t_flag *all_mod)
{
	long double f;
	long		num_start;
	long double	num_end;
	int			digit;
	int			count;
	int			res;
	int			check_0;
	int			check_start;
	//char		*fractional;
	//int			index;

	if (all_mod->length == 5)
		f = va_arg(all_arg, long double);
	else
		f = va_arg(all_arg, double);
	num_start = (long)f;
	ft_printf("%ld", num_start);
	write(1, ".", 1);
	if (num_start < 0)
	{
		f = f * -1;
		num_start = num_start * -1;
	}
	num_end = f - num_start;
	count = 6;
	res = 0;
	check_0 = 0;
	check_start = 0;
	while (count)
	{
		digit = (int)(num_end * 10);
		num_end = (num_end) * 10 - digit;
		if (digit > 0)
			check_start = 1;
		if (digit == 0 && !check_start)
			check_0++;
		res = res * 10 + digit;
		count--;
	}
	if ((int)(num_end * 10) > 4)
		res++;
	if (check_0 > 0)
	{
		while (check_0 > 0)
		{
			write(1, "0", 1);
			check_0--;
		}
	}

	ft_printf("%d", res);
}

