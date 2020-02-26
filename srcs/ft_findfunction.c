#include "../includes/ft_printf.h"

int				ft_writespec(t_flag *all_mod, int check, long long nbr)
{
	if ((all_mod->spc == 'x' || all_mod->spc == 'X') && nbr != 0 \
	&& all_mod->f_sh == '#')
		return (2);
	if (all_mod->spc == 'o' && nbr != 0 && all_mod->f_sh == '#')
		return(1);
	return (0);
}

size_t			count_for_len(long long nbr, int base, t_flag *all_mod)
{
	int		count;
	int		copy;
	int		cpyspec;

	count = 0;
	cpyspec = nbr;
	copy = nbr;
	if (nbr < 0 || nbr == 0)
		count += 1;
	nbr < 0 ? nbr *= -1 : nbr;
	while (nbr > 0)
	{
		nbr /= base;
		count += 1;
	}
	if (all_mod->f_sh == '#')
	{
		if (copy != 0)
			count += ft_writespec(all_mod, 0, cpyspec);
	}
	return (count);
}

long long		ft_findtype(va_list all_arg, t_flag *all_mod)
{
	if (all_mod->len == 2 && ft_memchr("di", (int)all_mod->spc, 2))
		return ((short)va_arg(all_arg, int));
	if (all_mod->len == 3 && ft_memchr("di", (int)all_mod->spc, 2))
		return ((long)va_arg(all_arg, long));
	if (all_mod->len == 4 && ft_memchr("di", (int)all_mod->spc, 2))
		return ((long long)va_arg(all_arg, long long));
	if (!all_mod->len && ft_memchr("oxXu", (int)all_mod->spc, 4))
		return ((unsigned int)va_arg(all_arg, unsigned int));
	if (all_mod->len == 1 && ft_memchr("oxXu", (int)all_mod->spc, 4))
		return ((unsigned short)va_arg(all_arg, int));
	if (all_mod->len == 2 && ft_memchr("oxXu", (int)all_mod->spc, 4))
		return ((unsigned char)va_arg(all_arg, int));
	if (all_mod->len == 3 && ft_memchr("oxXu", (int)all_mod->spc, 4))
		return ((unsigned long)va_arg(all_arg, unsigned long));
	if (all_mod->len == 4 && ft_memchr("oxXub", (int)all_mod->spc, 5))
		return ((unsigned long long)va_arg(all_arg, unsigned long long));
	if (all_mod->spc == 'p')
		return (uintptr_t)(va_arg(all_arg, void*));
	else
		return (va_arg(all_arg, int));
}

int				*ft_itoa_base(va_list all_arg, t_flag *all_mod, int base)
{
	int			len;
	long long	nbr;
	char		*sign;

	nbr = ft_findtype(all_arg, all_mod);
	sign = nbr >= 0 ? "+" : "-";
	len = count_for_len(nbr, base, all_mod);
	nbr < 0 ? nbr *= -1 : nbr;
	all_mod->res = all_mod->res + len;
	(*sign == '-') ? write(1, sign, 1) : 0;
	/*if (nbr == 0 && all_mod->spc == 'o' && all_mod->prc < 0)
	{
			ft_outzero(all_mod);
			return(&all_mod->res);
	}*/
	if (nbr == 0 && all_mod->width <= 0 && all_mod->prc <= 0)
	{
		ft_outzero(all_mod);
		return(&all_mod->res);
	}
	if (all_mod->spc == 'p')
		ft_spec_p(all_mod, nbr, base, len);
	else
		ft_findout(all_mod, nbr, base, len);
	return (0); //nadya
}

size_t			ft_findfunction(va_list all_arg, t_flag *all_mod)
{
	if (all_mod->spc == 'c')
		ft_spec_c(all_arg, all_mod);
	if (all_mod->spc == 's')
		ft_spec_s(all_arg, all_mod);
	if ((all_mod->spc == 'd') || (all_mod->spc == 'i') || (all_mod->spc == 'u'))
		ft_itoa_base(all_arg, all_mod, 10);
	if (all_mod->spc == 'b')
		ft_itoa_base(all_arg, all_mod, 2);
	if (all_mod->spc == 'o')
		ft_itoa_base(all_arg, all_mod, 8);
	if ((all_mod->spc == 'X') || (all_mod->spc == 'x') || (all_mod->spc == 'p'))
		ft_itoa_base(all_arg, all_mod, 16);
	if (all_mod->spc == '%')
		ft_percent(all_mod);
	if (all_mod->spc == 'f')
		ft_spec_f(all_arg, all_mod);
	return (0);
}
