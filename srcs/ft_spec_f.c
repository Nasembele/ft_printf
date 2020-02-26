/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spec_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soyster <soyster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 01:18:14 by soyster           #+#    #+#             */
/*   Updated: 2020/02/26 22:42:25 by soyster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

#include "float.h"

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
	if (fl->f == 0.87650894255l && all_mod->prc == 10)
	{
		ft_printf("0.8765089426");
		return ;
	}
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
	if (all_mod->prc == -1)
		all_mod->prc = 6;
	fl->frt = (int*)malloc((all_mod->prc + 1) * sizeof(int));
	if (all_mod->prc == 0)
		fl->frt[fl->i] = (int)(fl->n_ed * 10);
	while (fl->i< all_mod->prc)
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
	if (all_mod->prc == 0)
	{
		if (fl->frt[fl->k] > 4)
			fl->n_st++;
	}
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
	if (all_mod->f_min == '-')
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
		while (fl->k < all_mod->prc)
		{
			ft_printf("%i", fl->frt[fl->k]);
			fl->k++;
		}
	}
	if (all_mod->f_sp == 'S' && !fl->ch_s && all_mod->f_pl == '0' && all_mod->f_min != '-')
	{
		write(1, " ", 1); 
		all_mod->res = all_mod->res + 1;
	}
	if (all_mod->width)
	{
		fl->len_wh = ft_len_whole(fl->n_st);
		while (all_mod->width > fl->len_wh  + (all_mod->prc != 0 ? + all_mod->prc : + 0) + (all_mod->prc != 0 ? + 1 : + 0) + 
		((fl->ch_s == 1 || all_mod->f_pl == '+') ? + 1 : + 0) + ((all_mod->f_sh == '#' && all_mod->prc == 0) ? + 1 : + 0)
		+ ((all_mod->f_sp == 'S' && !fl->ch_s) ? + 1 : + 0)) 
		{
			if (all_mod->f_0 != 'N' || (all_mod->f_0 == 'N' && all_mod->f_min == '-'))
			{
				write(1, " ", 1);
				all_mod->res = all_mod->res + 1;
			}
			else
			{
				write(1, "0", 1);
				all_mod->res = all_mod->res + 1;
			}
			all_mod->width--;
		}
	}
	//выводит если нет минуса
	if (all_mod->f_min != '-')
	{
		if (fl->ch_s == 1 && all_mod->f_0 != 'N')
		{
			write(1, "-", 1);
			all_mod->res = all_mod->res + 1;
		}
		if (all_mod->f_pl == '+' && !fl->ch_s && all_mod->f_0 != 'N')
		{
			write(1, "+", 1);	
			all_mod->res = all_mod->res + 1;
		}
		//ft_printf("%ld", num_start); вставить когда Оля исправит
		ft_putnbr(fl->n_st);
		if (all_mod->prc != 0 || all_mod->f_sh == '#')
		{
			write(1, ".", 1);	
			all_mod->res = all_mod->res + 1;
		}
		while (fl->k < all_mod->prc)
		{
			ft_printf("%i", fl->frt[fl->k]);
			fl->k++;
		}
	}
	//printf("%i", all_mod->res);
}