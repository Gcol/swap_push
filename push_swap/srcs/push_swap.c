#include <push_swap.h>
#include "libft.h"


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
  if (sens == 2)
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

/*
static int		issorted(t_pile *pile, int until, int apile)
{
	return (ksorted(pile, apile) >= until);
}


void			sort3(t_pile **p1, t_pile **p2, int until, int apile)
{
	int		a;
	int		b;
	int		c;

	a = (apile) ? (*p1)->n : (*p2)->next->n;
	b = (apile) ? (*p1)->next->n : (*p2)->n;
	if (until == 3 && !issorted((apile) ? *p1 : *p2, 3, apile))
	{
		a = (apile) ? (*p1)->n : (*p2)->next->next->n;
		b = (apile) ? (*p1)->next->n : (*p2)->next->n;
		c = (apile) ? (*p1)->next->next->n : (*p2)->n;
		if ((apile && a < b && b > c) || (!apile && a > b && b < c))
		{
			doinstruct((apile) ? RA : RB, p1, p2);
			doinstruct((apile) ? SA : SB, p1, p2);
			doinstruct((apile) ? RRA : RRB, p1, p2);
		}
		else
			doinstruct((apile) ? SA : SB, p1, p2);
		sort3(p1, p2, until, apile);
	}
	else if (until == 2 && a > b)
		doinstruct((apile) ? SA : SB, p1, p2);
}

int				act(t_pile **p1, t_pile **p2, int apile, int pivot)
{
	if ((apile && (*p1)->n < pivot) || (!apile && (*p2)->n >= pivot))
	{
		doinstruct((apile) ? PB : PA, p1, p2);
		return (1);
	}
	else
		doinstruct((apile) ? RA : RB, p1, p2);
	return (0);
}

void			quicksort(t_piles p, int until, int apile, int fiter)
{
	int		i;
	int		reset;
	int		pivot;

	i = 0;
	reset = 0;
	pivot = median((apile) ? *(p.p1) : *(p.p2), until);
	if (issorted((apile) ? *(p.p1) : *(p.p2), until, apile))
		return ;
	while (until > 3 && i < (until / 2) + (until % 2 && !apile) && ++reset)
		i += act(p.p1, p.p2, apile, pivot);
	while ((!fiter || !apile) && (reset--) - i)
		doinstruct((apile) ? RRA : RRB, p.p1, p.p2);
	if (until - i <= 3)
		sort3(p.p1, p.p2, until - i, apile);
	else
		quicksort(p, until - i, apile, fiter);
	if (i)
		quicksort(p, i, !apile, apile && fiter);
	while (i--)
		doinstruct(apile ? PA : PB, p.p1, p.p2);

}*/



#include <stdio.h>

int median(t_dlist *stack, int size, int bigger, int lower)
{
  t_dlist *cur;
  t_dlist *tmp;
  int cmp;
  int position;

  position = 0;
  cur = stack;
  while( position != 0 && position != -1)
  {
      cmp = -1;
      position = 0;
      tmp = stack;
      if (tmp->dta >= lower && tmp->dta <= bigger)
        while(++cmp < size )
        {
          position += ((cur->dta < tmp->dta) ? 1 : -1);
          tmp = tmp->next;
        }
      if (position > 0)
        bigger = tmp->dta;
      else if (position < -1)
        lower = tmp->dta;
      cur = cur->next;
  }
  return(tmp->dta);
}

/*

while (until > 3 && i < (until / 2) + (until % 2 && !apile) && ++reset)
  i += act(p.p1, p.p2, apile, pivot);
while ((!fiter || !apile) && (reset--) - i)
  doinstruct((apile) ? RRA : RRB, p.p1, p.p2);
if (until - i <= 3)
  sort3(p.p1, p.p2, until - i, apile);
else
  quicksort(p, until - i, apile, fiter);
if (i)
  quicksort(p, i, !apile, apile && fiter);
while (i--)
  doinstruct(apile ? PA : PB, p.p1, p.p2);
*/

void  get_instruc(t_pushswap *tab, int target, int size)
{
  int pivot;
  int reset;

  reset = 0;
  pivot = median(((target) ? tab->stack_B : tab->stack_A), size, 2147483647, -2147483648);
  if (verif_pile(tab, size, ((target) ? 'D' : 'C')))
    return ;

}

int main(int argc, char **argv)
{
  t_pushswap *tab;

	tab = ft_memalloc_exit(sizeof(t_pushswap));
  if (argc > 1)
  {
	   get_argc_to_tab(tab, argc, argv, 0);
     get_instruc(tab, 0, ft_dlist_len(tab->stack_A));
    // affiche_stack(tab, 3);
   }
   return(0);
}
