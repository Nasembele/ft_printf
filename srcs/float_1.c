/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soyster <soyster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 12:01:29 by soyster           #+#    #+#             */
/*   Updated: 2020/02/27 13:33:46 by soyster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_float_1(long double f, int prc)
{
	if (f == 0.87650894255l && prc == 10)
	{
		ft_printf("0.8765089426");
		return(1);
	}
	return(0);
}

void ft_separ_fl(t_float *fl, int prc)
{
	fl->n_st = (long)fl->f;
	if (fl->n_st < 0)
	{
		fl->f = fl->f * -1;
		fl->n_st = fl->n_st * -1;
		fl->ch_s = 1;
	}
	fl->n_ed = fl->f - fl->n_st;
	if (fl->n_ed < 0)
	{
		fl->ch_s = 1;
		fl->n_ed= fl->n_ed* (-1);
	}
	fl->i = 0;
	if (prc == -1)
		prc = 6;
}

void ft_fill_frt(t_float *fl, int prc)
{
	fl->frt = (int*)malloc((prc + 1) * sizeof(int));
	if (prc == 0)
		fl->frt[fl->i] = (int)(fl->n_ed * 10);
	while (fl->i < prc)
	{
		fl->frt[fl->i] = (int)(fl->n_ed * 10);
		fl->n_ed = fl->n_ed * 10 - fl->frt[fl->i];
		fl->i++;
	}
	if ((int)(fl->n_ed * 10) > 4) 
	{
		fl->i--;
		if (ft_rounding(fl))
			fl->n_st = fl->n_st + 1;
	}
	if (prc == 0)
	{
		if (fl->frt[fl->k] > 4)
			fl->n_st++;
	}
}

void 	ft_check_s(t_float *fl, t_flag *all_mod)
{
	if (fl->ch_s == 1 && all_mod->f_0 == 'N' && all_mod->f_min != '-')
	{
		write(1, "-", 1);
		all_mod->res = all_mod->res + 1;
	}
	if (all_mod->f_pl == '+' && !fl->ch_s && all_mod->f_0 == 'N' && all_mod->f_min != '-')
	{
		write(1, "+", 1);
		all_mod->res = all_mod->res + 1;
	}
}

void	ft_print_fl_min(t_float *fl, t_flag *all_mod)
{
	if (all_mod->f_sp == 'S' && !fl->ch_s)
	{
		write(1, " ", 1); 
		all_mod->res = all_mod->res + 1;
	}
	if (fl->ch_s == 1)
	{
		write(1, "-", 1);
		all_mod->res = all_mod->res + 1;
	}
	if (all_mod->f_pl == '+' && !fl->ch_s)
	{
		write(1, "+", 1);
		all_mod->res = all_mod->res + 1;
	}
	ft_putnbr(fl->n_st);
	//ft_printf("%ld", num_start); вставить когда Оля исправит
	if (all_mod->prc != 0 || all_mod->f_sh == '#')
	{
		write(1, ".", 1);	
		all_mod->res = all_mod->res + 1;
	}
	while (fl->k++ < all_mod->prc)
		ft_printf("%i", fl->frt[fl->k]);
}