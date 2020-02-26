/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soyster <soyster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 01:18:14 by soyster           #+#    #+#             */
/*   Updated: 2020/02/26 22:41:40 by soyster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include "../libft/libft.h"

//#define ALL_FLAGS #0-+ 

typedef struct	s_flag
{
	const char	*format; //строка формата format
	int			i; //index для строки формата
	int			res; //кол-во напечатанных символов
	char		f_sh; //#
	char		f_0;  //0=N видит 0 только если он сразу после %
	char		f_min; //-
	char		f_pl;  //+
	char		f_sp;  //space = S
	int			width; // ширина
	int			prc; //точность precision
	int			len; //длина 1 - h, 2 - hh, 3 - l, 4 - ll, 5 - L
	char		spc; //спецификатор specifier
	//int			*frt; //дробная часть флота
	//int			ind; //индекс для дробной части флота
	
}				t_flag;

typedef struct	s_float
{
	long double	f; // храниться флот
	long		n_st;
	long double	n_ed;
	int			*frt; //дробная часть флота
	int			i; //индекс для дробной части флота
	int			k;
	int			ch_s; //чекает знак
	int			len_wh;
}				t_float;

void	ft_fill_fl(t_float *fl);
int		ft_rounding(t_float *fl);
void	ft_spec_f(va_list all_arg, t_flag *all_mod);
void	ft_outzero(t_flag *all_mod);
int	ft_spec_x(t_flag *all_mod, int len);
int	ft_wx(int len, char c);
int ft_sharp(t_flag *all_mod, int len);
void	ft_putnum(t_flag *all_mod, long long num, int base, int len);
int	ft_spec_x_add(t_flag *all_mod, int len);
void	ft_percent(t_flag *all_mod);
int		ft_simple_width(int simple_width, int result);
int base_put(t_flag *all_mod, long long num, int base);
void	ft_putstr_len(char const *str, size_t len_prec);
int		ft_spec_s(va_list all_arg, t_flag *all_mod);
int		ft_spec_c(va_list all_arg, t_flag *all_mod);
int	ft_width(t_flag *all_mod, int len);
t_flag	*ft_free_allmod(t_flag *all_mod);
int ft_spec_p(t_flag *all_mod, long long num, int base, int len);
void		ft_put_dec(t_flag *all_mod, long long num, int base);
int		ft_length(va_list all_arg, t_flag *all_mod);
int		ft_spec(va_list all_arg, t_flag *all_mod);
int		ft_flags(va_list all_arg, t_flag *all_mod);
int		ft_wid_and_prec(va_list all_arg, t_flag *all_mod);
int		ft_printf(const char *format, ...);
void ft_findout(t_flag *all_mod, long long num, int base, int len);
size_t ft_findfunction(va_list all_arg, t_flag *all_mod);
int   *ft_itoa_base(va_list all_arg, t_flag *all_mod, int base);
size_t	count_for_malloc(long long nbr, int base);

#endif
