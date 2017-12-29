/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   little_tri.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 15:42:09 by gcollett          #+#    #+#             */
/*   Updated: 2017/12/29 15:44:34 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

void	little_tri(t_pushswap *tab, char size)
{
	if (verif_pile(tab, size, 'C'))
		return ;
	if (size == 2)
		execute_instruction(tab, 0, SWITCH);
	else
	{
		if (tab->stack_a->dta > tab->stack_a->next->dta
				&& tab->stack_a->dta > tab->stack_a->next->next->dta)
			execute_instruction(tab, 0, ROTATE);
		if (tab->stack_a->dta > tab->stack_a->next->dta)
			execute_instruction(tab, 0, SWITCH);
		if (tab->stack_a->dta < tab->stack_a->next->dta
				&& !verif_pile(tab, size, 'C'))
			execute_instruction(tab, 0, D_ROTATE);
		little_tri(tab, size);
	}
}

void	tri5(t_pushswap *tab, char size)
{
	int	tmp;
	int	cnt;

	tmp = size - 2;
	while (--tmp > 0)
		execute_instruction(tab, 1, PUSH + 10);
	little_tri(tab, 3);
	if (tab->stack_b->dta < tab->stack_b->next->dta)
		execute_instruction(tab, 1, SWITCH);
	tmp = size - 2;
	while (--tmp)
	{
		cnt = 3;
		while (tab->stack_b->dta > tab->stack_a->dta && cnt)
		{
			execute_instruction(tab, 0, D_ROTATE);
			--cnt;
		}
		execute_instruction(tab, 0, PUSH);
	}
}
