/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 05:34:50 by gcollett          #+#    #+#             */
/*   Updated: 2017/08/28 20:16:08 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <libft.h>
#include <checker.h>
#include <fcntl.h>

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

t_dlist	*add_stack(char *str, t_dlist *stack, t_dlist *res)
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
				tab->stack_A = add_stack(arg[index_s] + cnt_c, tab->stack_A, NULL);
			else if (state % 2 == 0 && ft_strchr("+-", arg[index_s][cnt_c]))
				state += 1;
			else if (ft_strchr("1234567890", arg[index_s][cnt_c]))
				state += (state < 2) ? 2 : 0;
			else
				ft_exit(2);
		}
		if (ft_strchr("1234567890", arg[index_s][cnt_c]))
			tab->stack_A = add_stack(arg[index_s], tab->stack_A, NULL);
		else
			ft_exit(2);
	}
}

//attention segfault sauvage avec RRR . A voir si c'est par ce que B est vide

void	execute_instruction(t_pushswap *t, int choice, int inst)
{
	t_dlist	**id;
	int		tmp;

	if (choice == 3 && !(choice = 0))
		execute_instruction(t, 1, inst);
	id = choice == 0 ? &(t->stack_A) : &(t->stack_B);
	if (inst == PUSH)
	{
		if ((choice == 0) ? t->stack_B : t->stack_A)
		{
			ft_dlist_add(id, 0, ((choice == 0) ? t->stack_B : t->stack_A)->dta);
			ft_dlist_remove(((choice == 0) ? &t->stack_B : &t->stack_A), 0);
		}
	}
	else if (inst == D_ROTATE && (*id) && (*id)->prev)
		(*id) = (*id)->prev;
	else if (inst == ROTATE && (*id) && (*id)->next)
		(*id) = (*id)->next;
	else if (inst == SWITCH && (*id) && (*id)->next)
	{
		tmp = (*id)->dta;
		(*id)->dta = (*id)->next->dta;
		(*id)->next->dta = tmp;
	}
}

void launch_instruction(t_pushswap *tab, int len, int choice)
{
	char *str;

	while(get_next_line(0, &str) > 0)
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
    //affiche_stack(tab, 3, ft_dlist_len(tab->stack_A));
  	free(str);
	}
}

void ft_dlist_make_circular(t_dlist *tab)
{
  t_dlist *tmp;

  tmp = tab;
  while (tmp && tmp->next)
    tmp = tmp->next;
  tmp->next = tab;
  tab->prev = tmp;
}

void  verif_pile(t_pushswap *tab)
{
  t_dlist *tmp;
  char sens;

  sens = 2;
  if (!tab->stack_B)
  {
    tmp = tab->stack_A->next;
    if (tab->stack_A->dta < tmp->dta)
      sens = 'C';
    while(tmp->next != tab->stack_A && sens != 2)
    {
      if ((tmp->dta > tmp->next->dta && sens == 'C'))
        sens = 2;
      tmp = tmp->next;
    }
  }
  if (sens == 2)
    write(1, "KO\n", 3);
  else
    write(1, "OK\n", 3);
}

//pense a vérifier le nombre d'argument argc avant de segauflt
int main(int argc, char **argv)
{
	t_pushswap *tab;

	tab = ft_memalloc_exit(sizeof(t_pushswap));
  if (argc > 1)
  {
	   get_argc_to_tab(tab, argv, 0, argc);
     ft_dlist_make_circular(tab->stack_A);
   }
	launch_instruction(tab, 0, 0);
	verif_pile(tab);
  while(1);
	return (0);
}
