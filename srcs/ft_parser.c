/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soyster <soyster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 00:57:33 by soyster           #+#    #+#             */
/*   Updated: 2020/02/26 21:42:54 by soyster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_flags(va_list all_arg, t_flag *all_mod)
{
    while (all_mod->format[all_mod->i] == '#' || \
    all_mod->format[all_mod->i] == '0' || all_mod->format[all_mod->i] == '-' \
    || all_mod->format[all_mod->i] == '+' || all_mod->format[all_mod->i] == ' ')
    {
        if (all_mod->format[all_mod->i] == '#')
            all_mod->f_sh = '#';
        if (all_mod->format[all_mod->i] == '0')
		   	all_mod->f_0 = 'N';
        if (all_mod->format[all_mod->i] == '-')
	    	all_mod->f_min = '-';
	    if (all_mod->format[all_mod->i] == '+')
	    	all_mod->f_pl = '+';
	    if (all_mod->format[all_mod->i] == ' ')
		    all_mod->f_sp = 'S';
        all_mod->i++;
    }
//    printf("flags = %c%c%c%c%c\n", all_mod->flag_sh, all_mod->flag_0, all_mod->flag_min, \
    all_mod->flag_pl, all_mod->flag_sp); // проверка
    return (0);
}

int	ft_wid_and_prec(va_list all_arg, t_flag *all_mod)
{
    int check_prec;

    check_prec = 0;    
    while(ft_isdigit(all_mod->format[all_mod->i]) \
    || all_mod->format[all_mod->i] == '.')
    {
        if (all_mod->format[all_mod->i] == '.')
        {
            check_prec = 1;
        	all_mod->prc = 0; //?!?!
			all_mod->i++;
        }
        if (check_prec == 0)
        {
            if (!(all_mod->width))
			    all_mod->width = all_mod->format[all_mod->i] - '0';
		    else
			    all_mod->width = all_mod->width * 10 + \
			    (all_mod->format[all_mod->i] - '0');
        }
        else
        {
			if (!ft_isdigit(all_mod->format[all_mod->i])) //999
			{
				//all_mod->i++;
				return (0);//999
			} //999
			if (!all_mod->prc)
				all_mod->prc = all_mod->format[all_mod->i] - '0';
			else
				all_mod->prc = all_mod->prc * 10 + \
				(all_mod->format[all_mod->i] - '0');
        }
        all_mod->i++;
    }
   // printf("width = %i\nprecision = %i\n", all_mod->width, all_mod->precision); // проверка
    return (0);
}

int	ft_length(va_list all_arg, t_flag *all_mod)
{
    while (all_mod->format[all_mod->i] == 'h' || all_mod->format[all_mod->i] \
    == 'l' || all_mod->format[all_mod->i] == 'L')
	{
		if (all_mod->len == 1 || all_mod->len == 3)
		{
			if (all_mod->len == 1)
				all_mod->len = 2;
			else
				all_mod->len = 4;
		}
		else
		{		
			if (all_mod->format[all_mod->i] == 'h')
				all_mod->len = 1;
			if (all_mod->format[all_mod->i] == 'l')
				all_mod->len = 3;
			if (all_mod->format[all_mod->i] == 'L')
				all_mod->len = 5;
		}
		all_mod->i++;
	}
    //printf("length = %i\n", all_mod->length); // проверка
    return (0);
}

int	ft_spec(va_list all_arg, t_flag *all_mod)
{
    all_mod->spc = all_mod->format[all_mod->i];
    all_mod->i++;
    //printf("spec = %c\n\n", all_mod->specifier); // проверка
    return (0);
}
