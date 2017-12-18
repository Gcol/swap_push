/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 19:19:52 by gcollett          #+#    #+#             */
/*   Updated: 2017/12/18 19:31:22 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

void	fill_buffer(t_pushswap *tab, char *test)
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

void	read_buffer(t_pushswap *tab)
{
	tab->registre = tab->origine;
	while (tab->registre)
	{
		write(1, tab->registre->reg, tab->registre->index);
		tab->registre = tab->registre->next;
	}
}

int		main(int argc, char **argv)
{
	t_pushswap	*tab;

	tab = ft_memalloc_exit(sizeof(t_pushswap));
	tab->registre = ft_memalloc_exit(sizeof(t_buffer));
	tab->origine = tab->registre;
	if (argc > 1)
	{
		get_argc_to_tab(tab, argv, -1, argc);
		ft_dlist_make_circular(tab->stack_a);
		get_instruc(tab, ft_dlist_len(tab->stack_a), 0, 1);
		read_buffer(tab);
	}
	return (0);
}
