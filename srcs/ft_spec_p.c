/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spec_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soyster <soyster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 01:18:14 by soyster           #+#    #+#             */
/*   Updated: 2020/02/05 17:59:29 by mleticia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_spec_p(t_flag *all_mod, char *pointer)
{
	int len;

	len = 0;
	if (all_mod->flag_min == '-')
	{
		write(1, "0x10", 4);
		while (pointer[len])
		{
			write(1, &pointer[len], 1);
			len++;
		}
	}
	ft_width(all_mod, 11);
	if (all_mod->flag_min != '-')
	{
		write(1, "0x10", 4);
		while (pointer[len])
		{
			write(1, &pointer[len], 1);
			len++;
		}
	}
	return (0);
}