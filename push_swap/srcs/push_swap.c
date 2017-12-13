#include <push_swap.h>
#include "libft.h"
#include <limits.h>

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

void  execute_instruction(t_pushswap *tab, int choice, int inst, char *registre)
{
  t_dlist **target;
	int tmp;

	tab->registre = ft_stradd(tab->registre, registre, 0, 1);
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


int  verif_pile(t_pushswap *tab, int size, char sens)
{
  t_dlist *tmp;
  int cmp;

  cmp = -1;
  if (sens == 'C')
    tmp = tab->stack_A;
  else
    tmp = tab->stack_B;
  while(++cmp < size && tmp->next != tab->stack_A && sens != 2)
  {
    if ((tmp->dta > tmp->next->dta && sens == 'C') ||
    (tmp->dta < tmp->next->dta && sens == 'D'))
      sens = 2;
    tmp = tmp->next;
  }
  if (sens != 2)
    return(1);
  else
    return(0);
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
		else if ((state == 0 && !ft_isspace(arg[index_s][index_c])) ||
     (state == 1 && !ft_strchr("1234567890",arg[index_s][index_c])))
         ft_exit(2);

	}
  tmp = tab->stack_A;
  while(tmp && tmp->next)
    tmp = tmp->next;
  tmp->next = tab->stack_A;
  tab->stack_A->prev = tmp;
}

int median(t_dlist *stack, int size, int bigger, int lower)
{
  t_dlist *cur;
  t_dlist *tmp;
  int cmp;
  int position;

  position = 1;
  cur = stack;
  while( position != 0 && position != -1)
  {
    //printf("bigger = %d lower = %d position = %d cur-Nb = %ld\n", bigger, lower, position, cur->dta);
      cmp = -1;
      tmp = stack;
      position = 0;
      //if ((cur->dta >= lower && cur->dta <= bigger) && !(position = 0))
        while(++cmp < size )
        {
					if (cur->dta < tmp->dta)
						position += 1;
					else if (cur->dta > tmp->dta)
						position -=1;
          tmp = tmp->next;
        }
      if (position < 0)
        bigger = cur->dta;
      else if (position > 1)
        lower = cur->dta;
      cur = cur->next;
  }
  return(cur->prev->dta);
}

void 	push_to_stack_median(t_pushswap *tab, int pivot)
{
	t_dlist *tmp;

	tmp = NULL;
  //printf("pivot = %d\n", pivot);
	while(tab->stack_A != tmp)
	{
		if (tab->stack_A->dta >= pivot)
			execute_instruction(tab, 1, PUSH, "PB\n");
    else if (!tmp)
      tmp = tab->stack_A;
    tab->stack_A = tab->stack_A->next;
	}
}

void tri_stack(t_pushswap *tab)
{
  if (tab->stack_A)
    return;
}

void  get_instruc(t_pushswap *tab, int size)
{
  if (verif_pile(tab, size, 'C'))
    return ;
	push_to_stack_median(tab, median(tab->stack_A, size, INT_MAX, INT_MIN));
  tri_stack(tab);
}

int main(int argc, char **argv)
{
  t_pushswap *tab;

	tab = ft_memalloc_exit(sizeof(t_pushswap));
  tab->registre = ft_memalloc_exit(1);
  if (argc > 1)
  {
	   get_argc_to_tab(tab, argc, argv, 0);
     get_instruc(tab, ft_dlist_len(tab->stack_A));
     affiche_stack(tab, 3);
   }
   return(0);
}
