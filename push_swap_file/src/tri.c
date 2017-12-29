/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 19:22:12 by gcollett          #+#    #+#             */
/*   Updated: 2017/12/18 19:22:31 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>


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
	if ((!cible && (tab->stack_a->dta < pivot))
			|| (cible && (tab->stack_b->dta >= pivot)))
	{
		execute_instruction(tab, !cible, PUSH + !cible * 10);
		return (1);
	}
	else
		execute_instruction(tab, cible, ROTATE + cible * 10);
	return (0);
}

void	tri_stack_3(t_pushswap *tab, int size, int cible)
{
	if (!verif_pile(tab, size - 1, (cible) ? 'D' : 'C'))
	{
		if (!verif_pile(tab, 1, (cible) ? 'D' : 'C'))
			execute_instruction(tab, cible, SWITCH + cible * 10);
		else
		{
			execute_instruction(tab, cible, ROTATE + cible * 10);
			execute_instruction(tab, cible, SWITCH + cible * 10);
			execute_instruction(tab, cible, D_ROTATE + cible * 10);
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
	if (verif_pile(tab, size, (cible) ? 'D' : 'C') || size == 1)
		return ;
	pivot = median((!cible) ? tab->stack_a : tab->stack_b, size, -1, INT_MAX);
	while (size > 3 && nb_supm < (size / 2) + (size % 2 && cible) && ++nb_rot)
		nb_supm += push_to_stack_median(tab, cible, pivot);
	while ((cible || !fiter) && (nb_rot--) - nb_supm)
		execute_instruction(tab, cible, D_ROTATE + cible * 10);
	if (nb_supm && cible)
		get_instruc(tab, nb_supm, !cible, 0);
	if (size - nb_supm <= 3)
		tri_stack_3(tab, size - nb_supm, cible);
	else
		get_instruc(tab, size - nb_supm, cible, (fiter == 2) ? --fiter : fiter);
	if (nb_supm && !cible)
		get_instruc(tab, nb_supm, !cible, (fiter == 2) ? 1 : 0);
	while (nb_supm--)
		execute_instruction(tab, cible, PUSH + cible * 10);
}
