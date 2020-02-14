//
// Created by Magorian Leticia on 04/02/2020.
//

#include "../includes/ft_printf.h"

int	ft_widthx(int width, int len, int prec)
{
	while (width > len)
	{
		if (width > prec && prec >= 0)
			write(1, " ", 1);
		else
			write(1, "0", 1);
		width--;
	}
	while (len < prec)
	{
		write(1, "0", 1);
		prec--;
	}
	return (0);
}

int	ft_spec_x(t_flag *all_mod, char *pointer)
{
	int len;
	int len_width;

	len = ft_strlen(pointer);
	len_width = len;
	if (all_mod->precision == 0 && !all_mod->width) // ?!?!
		return (0);				 //?!?!
	if (all_mod->precision == 0 && all_mod->width)
	{
		ft_simple_width(all_mod->width, all_mod->result);
		return (0);
	}
	else if (all_mod->flag_min != '-')
	{
		if (all_mod->flag_0 == 'N')
			ft_widthx(all_mod->width, len_width, all_mod->precision);
		else if(all_mod->precision > 0)
			ft_widthx(all_mod->width, len_width, all_mod->precision);
		else
			ft_widthx(all_mod->width, len_width, 0);
	}
	//if (all_mod->precision > 0 && all_mod->precision > len && all_mod->width == 0)
	// 	ft_widthx(all_mod->width, len_width, all_mod->precision);
	ft_putstr_len(pointer, len);
	if (all_mod->flag_min == '-')
	{
		len = all_mod->width - len_width;
		ft_widthx(all_mod->width, len_width, 0);
	}
	all_mod->result = all_mod->result + len; // результат сделать
	return (0);
}
