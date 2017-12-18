
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

void	execute_instruction(t_pushswap *t, int choice, int inst)
{
	t_dlist	**id;
	int		tmp;

	fill_buffer(t, choice_register(choice, inst));
	if (choice == 3 && !(choice = 0))
		execute_instruction(t, 1, inst);
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
}

char      *choice_register(int choice, int inst)
	{
	        char    *res;
	        int             len;

	        res = ft_memalloc_exit(4);
	        if (inst == D_ROTATE)
	        {
	                len = 2;
	                res[1] = 'r';
	        }
	        else
	                len = 1;
	        res[len + 1] = '\n';
	        if (inst == D_ROTATE || inst == ROTATE)
	                res[0] = 'r';
	        else if (inst == SWITCH)
	                res[len - 1] = 's';
	        else if (inst == PUSH)
	                res[len - 1] = 'p';
	        if (choice == 0)
	                res[len] = 'a';
	        else if (choice == 1)
	                res[len] = 'b';
	        else
	                res[len] = res[len - 1];
	        return (res);
	}
