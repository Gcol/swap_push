/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 05:34:50 by gcollett          #+#    #+#             */
/*   Updated: 2017/12/18 19:12:51 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <checker.h>

void	verif_pile(t_pushswap *tab)
{
	t_dlist	*tmp;
	char	sens;

	sens = 2;
	if (!tab->stack_b)
	{
		tmp = tab->stack_a->next;
		if (tab->stack_a->dta < tmp->dta)
			sens = 'C';
		while (tmp->next != tab->stack_a && sens != 2)
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

int		main(int argc, char **argv)
{
	t_pushswap *tab;

	if (argc > 1)
	{
		tab = ft_memalloc_exit(sizeof(t_pushswap));
		get_argc_to_tab(tab, argv, 0, argc);
		ft_dlist_make_circular(tab->stack_a);
		launch_instruction(tab, 0, 0);
		verif_pile(tab);
	}x
	return (0);
}
