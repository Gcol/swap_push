/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 19:21:01 by gcollett          #+#    #+#             */
/*   Updated: 2017/12/18 19:21:59 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

t_dlist	*add_st(char *str, t_dlist *stack, t_dlist *res)
{
	long long	value;
	int			test;

	test = ft_atoi(str);
	value = ft_atoll(str);
	if (test != value)
		ft_exit(2);
	if (!stack)
	{
		res = ft_memalloc_exit(sizeof(t_dlist));
		res->dta = test;
	}
	else
	{
		res = stack;
		while (res->prev && res->dta != test)
			res = res->prev;
		if (res->dta == test)
			ft_exit(2);
		res->prev = ft_memalloc_exit(sizeof(t_dlist));
		res->prev->dta = test;
		res->prev->next = res;
		res = res->prev;
	}
	return (res);
}

void	get_argc_to_tab(t_pushswap *tab, char **arg, long cnt_c, int index_s)
{
	int state;
	int i;

	i = 0;
	while (--index_s && !(state = 0))
	{
		cnt_c = ft_strlen(arg[index_s]);
		while (--cnt_c)
		{
			if (ft_isspace(arg[index_s][cnt_c]) && state >= 2 && !(state = 0))
				tab->stack_a = add_st(arg[index_s] + cnt_c, tab->stack_a, NULL);
			else if (state == 2 && ft_strchr("+-", arg[index_s][cnt_c]))
				state += 1;
			else if (ft_strchr("1234567890", arg[index_s][cnt_c]))
				state += (state < 2) ? 2 : 0;
			else
				ft_exit(2);
		}
		if (ft_strchr("1234567890", arg[index_s][cnt_c])
		|| ((state == 2) && ft_strchr("+-", arg[index_s][cnt_c])))
			tab->stack_a = add_st(arg[index_s], tab->stack_a, NULL);
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
	id = (choice == 0) ? &t->stack_a : &t->stack_b;
	if (inst == PUSH)
	{
		if ((choice == 0) ? t->stack_b : t->stack_a)
		{
			ft_dlist_add(id, 0, ((choice == 0) ? t->stack_b : t->stack_a)->dta);
			ft_dlist_remove(((choice == 0) ? &t->stack_b : &t->stack_a), 0);
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

char	*choice_register(int choice, int inst)
{
	char	*res;
	int		len;

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
