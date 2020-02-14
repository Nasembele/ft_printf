
int	ft_print_float1(t_flag *all_mod)
{
	t_double		num_f;
	unsigned long	mant;
	int				exp;

	num_f.ld = all_mod->f;
	mant = num_f.s_parts.mant;
	exp = num_f.s_parts.expon - 16383 - 63;//
	if (exp > 0)
		ft_pos_exp(exp, mant); 
	//else
	//	ft_neg_exp(exp, mant); //куда 3 случай???
	printf("%lu\n", (unsigned long)mant); //для дебага
	printf("%i", (int)exp); //для дебага
	return(0);
}

void	ft_spec_f(va_list all_arg, t_flag *all_mod)
{
	long double	f;

	if (all_mod->length == 5)
		f = va_arg(all_arg, long double);
	else
		f = va_arg(all_arg, double);
	all_mod->f = f;
	ft_print_float1(all_mod);
	return ;
}

int	ft_pos_exp(int exp, unsigned long mant)
{
	t_mant_list	*wh_float;

	while(mant)
	{
		wh_float = malloc(sizeof(t_mant_list));
		wh_float->base_list = 123;
		printf("%lu\n", wh_float->base_list);
		wh_float->next = malloc(sizeof(t_mant_list));
		wh_float = wh_float->next;
	}			
	return (0);
}