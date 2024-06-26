/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soyster <soyster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 01:18:14 by soyster           #+#    #+#             */
/*   Updated: 2020/02/27 12:58:10 by soyster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "float.h"

int	main(void)
{
	//ft_printf("%-05.0f\n", 7.3); // иногда segfault
	//ft_printf("%-05.0f", 7.3);
	//ft_printf("%.10Lf\n", 0.87650894255l);
	//ft_printf("%f\n", 145.1465675);
	//ft_printf("%f\n", 7.434);
	//printf("%.10Lf", 0.87650894255l);
	//printf("%f", -56.2012685);
	//printf("%.10Lf\n", 0.87650894255l);
	ft_printf("%.9Lf\n", -0.87650894255l);
	//printf("%.9Lf\n", 0.87650894255l);

	//t_printf("%.10Lf\n", 0.87650894255l);
	//ft_printf("%f\n", 0.000001); //иногда segfault
	//ft_printf("%f\n", 0.999999); //иногда segfault
	//ft_printf("%f\n", 43.43999949); //иногда segfault
	//ft_printf("%f\n", -985.765426499); //иногда segfault
	//printf("%f\n", -985.765426499); //иногда segfault
	
	//ft_printf("%f\n", FLT_MAX);
	//printf("%f\n", DBL_MAX);
	return (0);
}