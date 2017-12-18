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

void fill_buffer(t_pushswap *tab, char *trad)
{
	int i;

	i = -1;
	if (tab->buff->index + 4 > 500)
	{
		tab->buff->next = ft_memalloc_exit(sizeof(t_buffer));
		tab->buff = tab->buff->next;
	}
	while(trad[++i])
		tab->buff->reg[tab->buff->index++] = trad[i];
	free(trad);
}

void read_buffer(t_pushswap *tab)
{
	tab->buff = tab->origine;
	while(tab->buff)
	{
		write(1, tab->buff->reg, tab->buff->index);
		tab->buff = tab->buff->next;
	}
}

int		main(int argc, char **argv)
{
	t_pushswap	*tab;
	t_dlist		*tmp;

	tab = ft_memalloc_exit(sizeof(t_pushswap));
	tab->buff = ft_memalloc_exit(sizeof(t_buffer));
	tab->origine = tab->buff;
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
