#include "../includes/ft_printf.h"

void		ft_put_dec(t_flag *all_mod, long long num, int base)
{
	int		curr;
	char	*base_string;
	size_t	dec;

	dec = 1;
	base_string = all_mod->spc == 'X' ? "0123456789ABCDEF" : "0123456789abcdef";
	while ((dec * base < num) && dec < dec * base && (dec * base > 0))
		dec *= base;
	while (dec > 0)
	{
		if ((curr = num / dec) == base)
			write(1, "10", 2);
		else
			write(1, &base_string[curr], 1);
		num %= dec;
		dec /= base;
	}
}

void		ft_putnum(t_flag *all_mod, long long num, int base, int len)
{
	if (all_mod->f_sh == '#' && num != 0)
		ft_sharp(all_mod, len);
	else if (all_mod->f_min != '-' && len == 1 && all_mod->prc > 0)
		all_mod->res += ft_wx(all_mod->prc - 1, '0');
	else if (all_mod->width > len && all_mod->f_0 == 'N' \
	&& all_mod->f_sh == '#' && all_mod->prc == -1)
		all_mod->res += ft_wx(all_mod->width - len, '0');
	if (num == 0 && all_mod->prc == 0)
	{
		ft_wx(len, ' ');
		return ;
	}
	ft_put_dec(all_mod, num, base);
}

int			ft_spec_x(t_flag *all_mod, int len)
{
	if (all_mod->f_min == '-' && all_mod->prc > len && all_mod->f_sh != '#')
		return (ft_wx(all_mod->width - (all_mod->prc - len) - len, ' '));
	else if (all_mod->f_min == '-' && all_mod->prc > len && \
	all_mod->f_sh == '#')
	{
		all_mod->res += ft_wx(all_mod->width - (all_mod->prc - 2) - len, '0');
		if (len == 1)
			return (ft_wx(all_mod->width - all_mod->prc, ' '));
	}
	else if (all_mod->width > all_mod->prc && all_mod->prc > len \
	&& all_mod->f_sh != '#')
		return (ft_wx(all_mod->width - all_mod->prc, ' '));
	else if ((all_mod->width > all_mod->prc && all_mod->width > len) && \
		(all_mod->width - all_mod->prc > all_mod->width - len))
		return (ft_wx(all_mod->width - len, ' '));
	else if (all_mod->width - all_mod->prc > len && all_mod->f_min != '-')
	{
		all_mod->res += ft_wx(all_mod->width - all_mod->prc, ' ');
		if (len != 1)
			return (ft_wx(all_mod->width - all_mod->prc, '0'));
	}
	else if (all_mod->prc > 0 && all_mod->f_sh == '#')
		return (ft_wx(all_mod->prc - len, ' '));
	else if (all_mod->prc > 0 && len != 1)
		return (ft_wx(all_mod->prc - len, '0'));
	return (0); // nadya
}

int			ft_spec_x_add(t_flag *all_mod, int len)
{
	if (all_mod->prc < 1 && all_mod->width > len && all_mod->f_0 == 'N' \
	&& all_mod->f_sh != '#')
		return (ft_wx(all_mod->width - len, '0'));
	else if (all_mod->prc < 1 && all_mod->width > len && all_mod->f_0 != 'N')
		return (ft_wx(all_mod->width - len, ' '));
	else if (all_mod->width > all_mod->prc && all_mod->width > len && \
	all_mod->f_sh != '#' && all_mod->prc > -1 && all_mod->f_min != '-')
		return (ft_wx(all_mod->prc - len, '0'));
	else if (all_mod->width > all_mod->prc && all_mod->width > len \
	&& all_mod->f_0 == 'N' && all_mod->prc > -1 && all_mod->f_min != '-')
		return (ft_wx(all_mod->width - len, '0'));
	else if (len == 1 && all_mod->prc > -1)
	{
		all_mod->res += ft_wx(all_mod->width - all_mod->prc + len, '0');
		return (ft_wx(all_mod->width - all_mod->prc, ' '));
	}
	else if (len > all_mod->prc && all_mod->f_min == '-')
		return (ft_wx(all_mod->width - len, ' '));
	else if (all_mod->prc > -1 && all_mod->f_sh == '#' && all_mod->spc != 'o')
		return (ft_wx(all_mod->width - all_mod->prc - 2, ' '));
	else if (all_mod->prc > -1)
		return (ft_wx(all_mod->width - all_mod->prc, ' '));
	else
		return (0);
}

void		ft_findout(t_flag *all_mod, long long num, int base, int len)
{
	if (ft_memchr("oxXub", (int)all_mod->spc, 5))
	{
		if (all_mod->width > all_mod->prc && all_mod->width > len \
		&& all_mod->prc > 0 && all_mod->f_min != '-')
		{
			all_mod->res += ft_spec_x(all_mod, len);
			if (all_mod->prc > 0 && len != 1 && all_mod->f_sh != '#')
				all_mod->res += ft_spec_x_add(all_mod, len);
		}
		else if (all_mod->f_min == '-' && all_mod->f_sh != '#')
			all_mod->res += ft_wx(all_mod->prc - len, '0');
		else if (all_mod->prc > 0 && all_mod->f_sh != '#')
			all_mod->res += ft_spec_x(all_mod, len);
		else if (all_mod->width > len && all_mod->f_min != '-')
			all_mod->res += ft_spec_x_add(all_mod, len);
		ft_putnum(all_mod, num, base, len);
		if (all_mod->width > all_mod->prc && len > 1 && all_mod->f_min == '-')
			all_mod->res += ft_spec_x_add(all_mod, len);
		else if (all_mod->width > len && all_mod->f_min == '-')
			all_mod->res += ft_spec_x(all_mod, len);
	}
	else
		all_mod->res += base_put(all_mod, num, base);
}
