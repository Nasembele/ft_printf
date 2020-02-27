/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spec_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soyster <soyster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 01:18:14 by soyster           #+#    #+#             */
/*   Updated: 2020/02/27 13:37:04 by soyster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_len_whole(long num_start)
{
	int	len_whole;

	len_whole = 1;
	while(num_start / 10 > 0)
	{
		num_start = num_start / 10; 
		len_whole++;
	}
	return (len_whole);
}

int		ft_rounding(t_float *fl)
{
	int a;
	
	fl->frt[fl->i] = fl->frt[fl->i] + 1;
	if (fl->frt[fl->i] == 10)
	{
		fl->frt[fl->i] = 0;
		fl->i--;
		if (fl->i != -1)
			ft_rounding(fl);
		else
			return (1);
	}
	else
		return (0);
	if (fl->i == -1)
		return (1);
	else
		return (0);
}

void	ft_fill_fl(t_float *fl)
{
	fl->f = 0;
	fl->n_st = 0;
	fl->n_ed = 0;
	fl->frt = 0;
	fl->i = 0;
	fl->k = 0;
	fl->ch_s = 0;
	fl->len_wh = 0;
}

void	ft_spec_f(va_list all_arg, t_flag *all_mod)
{
	t_float	*fl;

	fl = malloc(sizeof(t_float));
	ft_fill_fl(fl);
	if (all_mod->len == 5)
		fl->f = va_arg(all_arg, long double);
	else
		fl->f = va_arg(all_arg, double);
	if (ft_float_1(fl->f, all_mod->prc))
		return ;
	ft_separ_fl(fl, all_mod->prc);
	ft_fill_frt(fl, all_mod->prc);
	ft_check_s(fl, all_mod);
	if (all_mod->f_min == '-')
		ft_print_fl_min(fl, all_mod);
	ft_print_sp(fl, all_mod);
	if (all_mod->f_min != '-')
		ft_print_fl(fl, all_mod);
	//printf("%i", all_mod->res);
}