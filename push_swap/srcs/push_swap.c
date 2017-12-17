/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 19:19:52 by gcollett          #+#    #+#             */
/*   Updated: 2017/12/17 22:25:05 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>
#include "libft.h"
#include <limits.h>

#include <stdio.h>

void	affiche_stack(t_pushswap *tab, int choix, int size)
{
	t_dlist	*tmp;
	int		cmp;

	cmp = -1;
	if (choix == 1 || choix == 3)
	{
		tmp = tab->stack_A;
		write(1, "Pile A : \n", 10);
		while (tmp && ++cmp < size)
		{
			printf("%ld\n", tmp->dta);
			tmp = (tmp->next == tab->stack_A) ? NULL : tmp->next;
		}
	}
	cmp = -1;
	if (choix == 2 || choix == 3)
	{
		tmp = tab->stack_B;
		write(1, "Pile B : \n", 10);
		while (tmp && ++cmp < size)
		{
			printf("%ld\n", tmp->dta);
			tmp = (tmp->next == tab->stack_B) ? NULL : tmp->next;
		}
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

void fill_buffer(t_pushswap *tab, char *test)
{
	int i;

	i = -1;
	if (tab->registre->index + 4 > 500)
	{
		tab->registre->next = ft_memalloc_exit(sizeof(t_buffer));
		tab->registre = tab->registre->next;
	}
	while (test[++i])
		tab->registre->reg[tab->registre->index++] = test[i];
	free(test);
}

void	execute_instruction(t_pushswap *t, int choice, int inst, int rec)
{
	t_dlist	**id;
	int		tmp;

	if (rec)
		fill_buffer(t, choice_register(choice, inst));
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
}

int		verif_pile(t_pushswap *tab, int size, char sens)
{
	t_dlist	*tmp;
	int		cmp;

	cmp = -1;
	if (sens == 'C')
		tmp = tab->stack_A;
	else
		tmp = tab->stack_B;
	while (++cmp < size && tmp->next != tab->stack_A && sens != 2)
	{
		if ((tmp->dta > tmp->next->dta && sens == 'C') ||
				(tmp->dta < tmp->next->dta && sens == 'D'))
			sens = 2;
		tmp = tmp->next;
	}
	if (sens != 2)
		return (1);
	else
		return (0);
}

int		median(t_dlist *stack, int size, int position, int bigger)
{
	int		lower;
	int		i;
	t_dlist	*cur;
	t_dlist	*tmp;

	cur = stack;
	lower = INT_MIN;
	while (position != 0 && position != 1)
	{
		position = (cur->dta > lower && cur->dta < bigger) ? 0 : position;
		tmp = stack;
		if (cur->dta > lower && cur->dta < bigger && (i = -1))
		{
				while (++i < size)
				{
					position -= (cur->dta < tmp->dta);
					position += (cur->dta > tmp->dta);
					tmp = tmp->next;
				}
			bigger = (position > 1) ? cur->dta : bigger;
			lower = (position < 0) ? cur->dta : lower;
		}
		cur = cur->next;
	}
	return (cur->prev->dta);
}

int		push_to_stack_median(t_pushswap *tab, int cible, int pivot)
{
	if ((!cible && (tab->stack_A->dta < pivot))
			|| (cible && (tab->stack_B->dta >= pivot)))
	{
		execute_instruction(tab, !cible, PUSH, 1);
		return (1);
	}
	else
		execute_instruction(tab, cible, ROTATE, 1);
	return (0);
}

void	tri_stack_3(t_pushswap *tab, int size, int cible)
{
	if (!verif_pile(tab, size - 1, (cible) ? 'D' : 'C'))
	{
		if (!verif_pile(tab, 1, (cible) ? 'D' : 'C'))
			execute_instruction(tab, cible, SWITCH, 1);
		else
		{
			execute_instruction(tab, cible, ROTATE, 1);
			execute_instruction(tab, cible, SWITCH, 1);
			execute_instruction(tab, cible, D_ROTATE, 1);
		}
		tri_stack_3(tab, size, cible);
	}
}

void	get_instruc(t_pushswap *tab, int size, int cible, int fiter)
{
	int	pivot;
	int	nb_rot;
	int	nb_supm;

	nb_rot = 0;
	nb_supm = 0;
	pivot = median((!cible) ? tab->stack_A : tab->stack_B, size, -1, INT_MAX);
	if (verif_pile(tab, size, (cible) ? 'D' : 'C'))
		return ;
	while (size > 3 && nb_supm < (size / 2) + (size % 2 && cible) && ++nb_rot)
		nb_supm += push_to_stack_median(tab, cible, pivot);
	while ((cible || !fiter) && (nb_rot--) - nb_supm)
		execute_instruction(tab, cible, D_ROTATE, 1);
	if (nb_supm && cible)
		get_instruc(tab, nb_supm, !cible, 0);
	if (size - nb_supm <= 3)
		tri_stack_3(tab, size - nb_supm, cible);
	else
		get_instruc(tab, size - nb_supm, cible, (fiter == 2) ? --fiter : fiter);
	if (nb_supm && !cible)
		get_instruc(tab, nb_supm, !cible, (fiter == 2) ? 1 : 0);
	while (nb_supm--)
		execute_instruction(tab, cible, PUSH, 1);
}

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

void read_buffer(t_pushswap *tab)
{
	tab->registre = tab->origine;
	while(tab->registre)
	{
		write(1, tab->registre->reg, tab->registre->index);
		tab->registre = tab->registre->next;
	}
}

int		main(int argc, char **argv)
{
	t_pushswap	*tab;
	t_dlist		*tmp;

	tab = ft_memalloc_exit(sizeof(t_pushswap));
	tab->registre = ft_memalloc_exit(sizeof(t_buffer));
	tab->origine = tab->registre;
	if (argc > 1)
	{
		get_argc_to_tab(tab, argv, -1, argc);
		tmp = tab->stack_A;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = tab->stack_A;
		tab->stack_A->prev = tmp;
		get_instruc(tab, ft_dlist_len(tab->stack_A), 0, 1);
		read_buffer(tab);
	}
	return (0);
}
