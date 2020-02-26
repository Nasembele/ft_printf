/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spec_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soyster <soyster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 01:18:14 by soyster           #+#    #+#             */
/*   Updated: 2020/02/26 15:13:30 by mleticia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_spec_p(t_flag *all_mod, long long num, int base, int len)
{
	if (all_mod->width > (len + 2) && all_mod->f_min != '-')
		all_mod->res += ft_wx(all_mod->width - len - 2, ' ');
	write(1, "0x", 2);
	all_mod->res += 2;
	ft_put_dec(all_mod, num, base);
	if (all_mod->width > (len + 2) && all_mod->f_min == '-')
		all_mod->res += ft_wx(all_mod->width - len - 2, ' ');
	return (0);
}
