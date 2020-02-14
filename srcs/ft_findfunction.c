//
// Created by Magorian Leticia on 17/01/2020.
//

#include "../includes/ft_printf.h"

size_t count_for_malloc(long long nbr, int base)
{
   int count;
   count = 0;
   if (nbr < 0 || nbr == 0)
   	count += 1;
   nbr < 0 ? nbr *= -1 : nbr;
   while (nbr)
   {
      nbr /= base;
      count += 1;
   }
   return (count);
}

long long ft_findtype(va_list all_arg, t_flag *all_mod)
{
	if (all_mod->length == 2 && ft_memchr("di", (int)all_mod->specifier, 2))
		return((short)va_arg(all_arg, int));
	if (all_mod->length == 3 && ft_memchr("di", (int)all_mod->specifier, 2))
		return((long)va_arg(all_arg, long));
	if (all_mod->length == 4 && ft_memchr("di", (int)all_mod->specifier, 2))
		return((long long)va_arg(all_arg, long long));
	if (!all_mod->length && ft_memchr("oxXu", (int)all_mod->specifier, 4))
		return((unsigned int)va_arg(all_arg, unsigned int));
	if (all_mod->length == 1 && ft_memchr("oxXu", (int)all_mod->specifier, 4))
		return((unsigned short)va_arg(all_arg, int));
	if (all_mod->length == 2 && ft_memchr("oxXu", (int)all_mod->specifier, 4))
		return((unsigned char)va_arg(all_arg, int));
	if (all_mod->length == 3 && ft_memchr("oxXu", (int)all_mod->specifier, 4))
		return((unsigned long)va_arg(all_arg, unsigned long));
	if (all_mod->length == 4 && ft_memchr("oxXu", (int)all_mod->specifier, 4))
		return((unsigned long long)va_arg(all_arg, unsigned long long));
	else
		return(va_arg(all_arg, int));
}

int ft_findout(t_flag *all_mod, char *pointer)
{
	int len;

	len = 0;
	if (ft_memchr("oxXu", (int)all_mod->specifier, 4))
		ft_spec_x(all_mod, pointer);
	else if (all_mod->specifier == 'p')
		ft_spec_p(all_mod, pointer);
	else
	{
		while (pointer[len])
		{
			write(1, &pointer[len], 1);
			len++;
		}
	}
	return(0);
}

int    *ft_itoa_base(va_list all_arg, t_flag *all_mod, int base)
{
	int       len;
	long long  nbr;
	char   *pointer;
	char   *base_string;

    len = 0;
    nbr = ft_findtype(all_arg, all_mod);
	base_string = all_mod->specifier == 'X' ? "0123456789ABCDEF" : "0123456789abcdef";
	len = count_for_malloc(nbr, base);
	nbr < 0 ? nbr *= -1 : nbr;
    all_mod->result = all_mod->result + len; // подсчет количества выведенных символов
    if (!(pointer = (char *)malloc(sizeof(char) * len + 1)))
        return (NULL);
    pointer[len] = '\0';
	if (nbr == 0)
	{
		pointer[0] = '0';
		len--;
	}
    while (nbr)
    {
        pointer[--len] = base_string[nbr % base];
        nbr /= base;
    }
	len == 1 ? pointer[0] = '-' : len;
	ft_findout(all_mod, pointer);
    return (0);
}

int ft_findfunction(va_list all_arg, t_flag *all_mod)
{
    if (all_mod->specifier == 'c')
        ft_spec_c(all_arg, all_mod);
    if (all_mod->specifier == 's')
        ft_spec_s(all_arg, all_mod);
    if ((all_mod->specifier == 'd') || (all_mod->specifier == 'i') || (all_mod->specifier == 'u'))
        ft_itoa_base(all_arg, all_mod, 10);
    if (all_mod->specifier == 'b')
        ft_itoa_base(all_arg, all_mod, 2);
    if (all_mod->specifier == 'o')
        ft_itoa_base(all_arg, all_mod, 8);
    if ((all_mod->specifier == 'X') || (all_mod->specifier == 'x') || (all_mod->specifier == 'p'))
        ft_itoa_base(all_arg, all_mod, 16);
	if (all_mod->specifier == '%')
		ft_percent(all_mod);
	if (all_mod->specifier == 'f')
		ft_spec_f(all_arg, all_mod);
    return(0);
}