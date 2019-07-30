/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reading.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soyster <soyster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 00:57:33 by soyster           #+#    #+#             */
/*   Updated: 2019/07/30 05:51:43 by soyster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_parse_format(va_list list, const char *format) 
// ищет в строке все флаги и заполняет структуру
// когда находит типи модификатор, ищет их в аргументах 
// передает в нужную функцию
{
	
	int		t;
	int		i;
	int		sum;

	sum = 0;
	printf("%s", format);
	i = 3;
	while (i)
	{
		t = va_arg(list, int);
		sum = sum + t;
		i--;
	}
	printf("%d", sum);
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list list;
	int		result;

	va_start(list, format);
	result = ft_parse_format(list, format);
	va_end(list);
	return (result);
}
