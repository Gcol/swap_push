/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 19:13:04 by gcollett          #+#    #+#             */
/*   Updated: 2017/12/18 19:14:00 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <checker.h>

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

void	launch_instruction(t_pushswap *tab, int len, int choice)
{
	char *str;

	while (get_next_line(0, &str) > 0)
	{
		choice = 4;
		len = ft_strlen(str);
		if (str[0] == str[1] && str[len] == str[len - 1]
				&& ft_c_in_str(str[0], "rs"))
			choice = 3;
		if (str[len - 1] == 'a' || str[len - 1] == 'b')
			choice = str[len - 1] - 'a';
		if (len == 2 && choice != 4)
			execute_instruction(tab, choice, str[0] - 'p');
		else if (str[0] == 'r' && len == 3 && choice != 4)
			execute_instruction(tab, choice, 1);
		else
			ft_exit(3);
		free(str);
	}
}
