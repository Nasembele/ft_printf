
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soyster <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 13:39:32 by soyster           #+#    #+#             */
/*   Updated: 2019/07/24 13:39:36 by soyster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

typedef enum    e_flag
{
    zero,
    plus,
    minus,
    sharp,
    star,
    apost,
    dollar,
    space
}               e_flag;

typedef enum    e_size
{
    l,
    ll,
    h,
    hh,
    L
}               e_size;

typedef enum    e_type
{
    c,
    s,
    p,
    i,
    d,
    o,
    u,
    x,
    X,
    f,
    F,
    e,
    E,
    g,
    G,
    b,
    r,
    k,
    n,
    a,
    A
}               e_type;

typedef struct  s_option
{
    int         isflags; // 1 - есть 0 - нет  
    e_flag      flags[8];
    int         width;
    int         precision;
    e_size      len;
    e_type      type;
    char        *content;
    size_t      content_size;
}               t_option;

t_option        *ft_format(char *s, size_t len) // определение спецификаторов
{
    t_option    *elements;    
    char        dot;
    int         count;

    count = 0;
    if (s != '%') // *?
    {
        elements->isflags = 0;
        elements->content = s;
        elements->content_size = len;
    }
    else if (*s++ == '%')
    {
        elements->isflags = 0;
        elements->content = *s++; // нуждается в тестах прибавит ли s++
        elements->content_size = len - 1;
    }
    else
    {
        if (s[len--] == 'c' || s[len--] == 's' || s[len--] == 'p' || s[len--] == 'i' ||
        s[len--] == 'd' || s[len--] == 'o' || s[len--] == 'x' || s[len--] == 'X' || s[len--] == 'f')
        if ((dot = ft_strchr(s, '.', len))) // уточнить как работает
        {
            while(ft_isnumber(dot++))
            {
                count ++;
            }
            if (++dot == '*')
            {
                elements->precision = -1;
            }
        }
    }
    return (elements);
}