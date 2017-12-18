
#include <push_swap.h>


t_dlist	*add_st(char *str, t_dlist *stack, t_dlist *res)
{
	long long	value;
	int			test;

	test = 0;
	test = ft_atoi(str);
	value = ft_atoll(str);
	if (test != value)
		ft_exit(2);
	if (!stack)
	{
		stack = ft_memalloc_exit(sizeof(t_dlist));
		stack->dta = test;
	}
	else
	{
		res = stack;
		while (res->next && res->dta != test)
			res = res->next;
		if (res->dta == test)
			ft_exit(2);
		res->next = ft_memalloc_exit(sizeof(t_dlist));
		res->next->dta = test;
		res->next->prev = res;
	}
	return (stack);
}


void	get_argc_to_tab(t_pushswap *tab, char **arg, long cnt_c, int argc)
{
	int index_s;
	int state;
	int i;

	i = 0;
	index_s = 0;
	while (++index_s < argc && !(state = 0))
	{
		cnt_c = ft_strlen(arg[index_s]);
		while (--cnt_c)
		{
			if (ft_isspace(arg[index_s][cnt_c]) && state >= 2 && !(state = 0))
				tab->stack_A = add_st(arg[index_s] + cnt_c, tab->stack_A, NULL);
			else if (state % 2 == 0 && ft_strchr("+-", arg[index_s][cnt_c]))
				state += 1;
			else if (ft_strchr("1234567890", arg[index_s][cnt_c]))
				state += (state < 2) ? 2 : 0;
			else
				ft_exit(2);
		}
		if (ft_strchr("1234567890", arg[index_s][cnt_c]))
			tab->stack_A = add_st(arg[index_s], tab->stack_A, NULL);
		else
			ft_exit(2);
	}
}

void	execute_instruction(t_pushswap *t, int choice, int inst, int write)
{
	t_dlist	**id;
	int		tmp;

	if (rec)
		fill_buffer(t, write, NULL);
	if (choice == 3 && !(choice = 0))
		execute_instruction(t, 1, inst, 0);
	id = (choice == 0) ? &t->stack_A : &t->stack_B;
	if (inst == PUSH)
	{
		if ((choice == 0) ? t->stack_B : t->stack_A)
		{
			ft_dlist_add(id, 0, ((choice == 0) ? t->stack_B : t->stack_A)->dta);
			ft_dlist_remove(((choice == 0) ? &t->stack_B : &t->stack_A), 0);
		}
	}
	else if (inst == D_ROTATE && *id && (*id)->prev)
		*id = (*id)->prev;
	else if (inst == ROTATE && *id && (*id)->next)
		*id = (*id)->next;
	else if (inst == SWITCH && *id && (*id)->next)
	{
		tmp = (*id)->dta;
		(*id)->dta = (*id)->next->dta;
		(*id)->next->dta = tmp;
	}
