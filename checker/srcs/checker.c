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


void affiche_stack(t_pushswap *tab, int choix)
{
  t_dlist *tmp;

	if (choix == 1 || choix == 3)
	{
    tmp = tab->stack_A;
		write(1, "Pile A : \n", 10);
		while(tmp)
		{
			printf("%ld\n", tmp->dta);
			tmp = (tmp->next == tab->stack_A) ? NULL : tmp->next;
		}
	}
	if (choix == 2 || choix == 3)
	{
    tmp = tab->stack_B;
		write(1, "Pile B : \n", 10);
		while(tmp)
		{
			printf("%ld\n", tmp->dta);
			tmp = (tmp->next == tab->stack_B) ? NULL : tmp->next;
		}
	}
}

t_dlist  *add_stack(char *str, t_dlist *stack, int test,t_dlist *res)
{
	long long value;

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
		while(res->next && res->dta != test)
			res = res->next;
		if (res->dta == test)
			ft_exit(2);
		res->next = ft_memalloc_exit(sizeof(t_dlist));
		res->next->dta = test;
		res->next->prev = res;
	}
	return(stack);
}

void get_argc_to_tab(t_pushswap *tab, int nb_arg, char **arg, int state)
{
	long   index_c;
  t_dlist  *tmp;
	int    index_s;

	index_s = 1;
	index_c = -1;
	while(state < 3)
	{
		if (!arg[index_s][++index_c] && !(index_c = 0))
		{
			tab->stack_A = add_stack(arg[index_s], tab->stack_A, 0, NULL);
			index_s += 1;
			state = (index_s < nb_arg) ? 0 : 3;
		}
		if (state == 0 && ft_strchr("+-1234567890",arg[index_s][index_c]))
			state = 1;
		if ((state == 0 && !ft_isspace(arg[index_s][index_c])) ||
     (state == 1 && !ft_strchr("1234567890",arg[index_s][index_c])))
			ft_exit(2);
	}
  tmp = tab->stack_A;
  while(tmp && tmp->next)
    tmp = tmp->next;
  tmp->next = tab->stack_A;
  tab->stack_A->prev = tmp;
}

//attention segfault sauvage avec RRR . A voir si c'est par ce que B est vide

void  execute_instruction(t_pushswap *tab, int choice, int inst, int tmp)
{
  t_dlist **target;

  if (choice == 3 && !(choice = 0))
    execute_instruction(tab, 1, inst, 0);
  if (choice == 0)
    target = &(tab->stack_A);
  if (choice == 1)
    target = &(tab->stack_B);
  if (inst == PUSH)
  {
    if ((choice == 0) ? tab->stack_B : tab->stack_A)
    {
      ft_dlist_add(target, 0, ((choice == 0) ? tab->stack_B : tab->stack_A)->dta);
      ft_dlist_remove(((choice == 0) ? &tab->stack_B : &tab->stack_A), 0);
    }
  }
  else if (inst == D_ROTATE && (*target) && (*target)->prev)
    (*target) = (*target)->prev;
  else if (inst == ROTATE && (*target) && (*target)->next)
      (*target) = (*target)->next;
  else if (inst == SWITCH && (*target) && (*target)->next)
  {
    tmp = (*target)->dta;
    (*target)->dta  = (*target)->next->dta;
    (*target)->next->dta = tmp;
  }
}

void launch_instruction(t_pushswap *tab, int len, int choice, int ind)
{
	char *str;
  int ind;

	while(get_next_line(0, &str) > 0)
	{
    ind = 0;
		choice = 4;
    while(ft_isspace(str[ind]))
      ind++;
    len = ft_strlen(str + ind);
    while(ft_isspace(str[ind + --len]))
      ;
		if (str[ind] == str[ind + 1] && str[ind + 1] == str[ind + ++len - 1]
       && ft_c_in_str(str[ind], "rs"))
			choice = 3;
		if (str[ind + len - 1] == 'a' || str[ind + len - 1] == 'b')
			choice = str[ind + len - 1] - 'a';
		if (len == 2 && choice != 4)
			execute_instruction(tab, choice, str[ind] - 'p', 0);
		else if (str[ind] == 'r' && len == 3 && choice != 4)
			execute_instruction(tab, choice, 1, 0);
		else
			ft_exit(3);
    affiche_stack(tab, 3);
  	free(str);
	}
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
    else if(tab->stack_A->dta > tmp->dta)
      sens = 'D';
    while(tmp->next != tab->stack_A && sens != 2)
    {
      if ((tmp->dta > tmp->next->dta && sens == 'C') ||
      (tmp->dta < tmp->next->dta && sens == 'D'))
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
	   get_argc_to_tab(tab, argc, argv, 0);
     affiche_stack(tab, 3);
   }
	launch_instruction(tab, 0, 0, 0);
	verif_pile(tab);
	return (0);
}
