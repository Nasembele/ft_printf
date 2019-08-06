
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnancy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 20:30:36 by fnancy            #+#    #+#             */
/*   Updated: 2019/07/03 20:30:36 by fnancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_FT_PRINTF_H
#define FT_LS_FT_PRINTF_H


# include "../libft/libft.h"
# include <stdarg.h>

typedef struct	s_format
{
	int 		pre;
	int 		f_len;
	int 		type;
	int 		size;
	char 		spec;
	char 		ispre;
	char 		sh;
	char		sign;
	char 		minus;
	char 		z_field;
}				t_format;

int 	ft_printf(const char *str, ...);

#endif