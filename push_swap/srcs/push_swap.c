#include <push_swap.h>
#include "libft.h"
#include <limits.h>

#include <stdio.h>

void affiche_stack(t_pushswap *tab, int choix, int size)
{
	t_dlist *tmp;
  int cmp;

  cmp = 0;
	if (choix == 1 || choix == 3)
	{
		tmp = tab->stack_A;
		write(1, "Pile A : \n", 10);
		while(tmp && ++cmp < size)
		{
			printf("%ld\n", tmp->dta);
			tmp = (tmp->next == tab->stack_A) ? NULL : tmp->next;
		}
	}
  cmp = 0;
	if (choix == 2 || choix == 3)
	{
		tmp = tab->stack_B;
		write(1, "Pile B : \n", 10);
		while(tmp && ++cmp < size)
		{
			printf("%ld\n", tmp->dta);
			tmp = (tmp->next == tab->stack_B) ? NULL : tmp->next;
		}
	}
}

char *choice_register(int choice, int inst)
{
	char *res;
	int len;

	res = ft_memalloc_exit(4);
	if (inst == D_ROTATE)
	{
		len = 2;
		res[1] = 'r';
	}
	else
		len = 1;
	res[len + 1] = '\n';
	if ( inst == D_ROTATE || inst == ROTATE)
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
		res[len] = res[len -1];
	return (res);
}

/*collicion avec la maniere de lancer RR*/

void  execute_instruction(t_pushswap *tab, int choice, int inst, int rec)
{
	t_dlist **target;
	int tmp;

	if (rec)
		tab->res = ft_stradd(tab->res, choice_register(choice, inst), 0, 1);
	if (choice == 3 && !(choice = 0))
		execute_instruction(tab, 1, inst, 0);
	target = choice == 0 ? &(tab->stack_A) : &(tab->stack_B);
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
		if ((ft_isspace(arg[index_s][index_c]) || (!arg[index_s][++index_c] && !(index_c = 0))))
		{
			tab->stack_A = add_stack(arg[index_s], tab->stack_A, 0, NULL);
			if (!ft_isspace(arg[index_s][index_c]))
				index_s += 1;
			else
				index_c++;
			state = (index_s < nb_arg) ? 0 : 3;
		}
		if (state == 0 && ft_strchr("+-",arg[index_s][index_c]))
			state = 1;
		else if (state != 3 && ((!ft_isspace(arg[index_s][index_c]) &&
						!ft_strchr("1234567890",arg[index_s][index_c])) ||
					(state == 1 && ft_strchr("+-",arg[index_s][index_c]))))
			ft_exit(2);
	}
	tmp = tab->stack_A;
	while(tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = tab->stack_A;
	tab->stack_A->prev = tmp;
}
/*
 **
 **  a voir bigger lower
 */


int median(t_dlist *stack, int size, int position, int cible)
{
	t_dlist *cur;
	t_dlist *tmp;
	int cmp;

	cur = stack;
	while( position != 0 && position != -1)
	{
		cmp = -1;
		tmp = stack;
		position = 0;
		while(++cmp < size)
		{
			if ((cur->dta < tmp->dta && !cible) || (cur->dta > tmp->dta && cible))
				position += 1;
			else if ((cur->dta > tmp->dta && !cible) || (cur->dta < tmp->dta && cible))
				position -=1;
			tmp = tmp->next;
		}
		cur = cur->next;
	}
	return(cur->prev->dta);
}

int 	push_to_stack_median(t_pushswap *tab, int cible, int pivot)
{
		if ((!cible && (tab->stack_A->dta < pivot))
    || (cible && (tab->stack_B->dta >= pivot)))
    {
      execute_instruction(tab, !cible, PUSH, 1);
      return(1);
    }
		else
        execute_instruction(tab, cible, ROTATE, 1);
    return(0);
}

void  tri_stack_3(t_pushswap *tab, int size, int cible)
{
	if (!verif_pile(tab, size - 1, (cible) ? 'D' : 'C'))
	{
		if (size == 3 )
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
		else
			execute_instruction(tab, cible, SWITCH, 1);
	}
}


void  get_instruc(t_pushswap *tab, int size, int cible, int first_iter)
{
  int pivot;
	int nb_rotate;
  int nb_sup_median;

  pivot = median((!cible) ? tab->stack_A : tab->stack_B, size, 1, cible);
  nb_rotate = 0;
  nb_sup_median = 0;
	if (verif_pile(tab, size, (cible) ? 'D' : 'C'))
	return;
  while (size > 3 && nb_sup_median < (size / 2) + (size % 2 && cible) && ++nb_rotate)
    nb_sup_median += push_to_stack_median(tab, cible, pivot);
  while ((cible || !first_iter) && (nb_rotate--) - nb_sup_median)
    execute_instruction(tab, cible, D_ROTATE, 1);
	if (size  - nb_sup_median <= 3)
    tri_stack_3(tab, size - nb_sup_median, cible);
	else
		get_instruc(tab, size - nb_sup_median, cible, first_iter);
  if (nb_sup_median)
		get_instruc(tab, nb_sup_median, !cible, !cible && first_iter);
  while (nb_sup_median--)
    execute_instruction(tab, cible, PUSH, 1);
}

int main(int argc, char **argv)
{
	t_pushswap *tab;

	tab = ft_memalloc_exit(sizeof(t_pushswap));
	tab->res = ft_memalloc_exit(1);
	if (argc > 1)
	{
		get_argc_to_tab(tab, argc, argv, 0);
		get_instruc(tab, ft_dlist_len(tab->stack_A), 0, 1);
    //affiche_stack(tab, 3, ft_dlist_len(tab->stack_A));
		printf("%s\n", tab->res);
	}
	return(0);
}
