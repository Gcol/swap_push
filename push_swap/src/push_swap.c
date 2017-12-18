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

void fill_buffer(t_pushswap *tab, int inst, char *trad)
{
	int i;

	i = -1;
	if (tab->buff->index == 500 || ((trad) && tab->buff->index + 4 == 500)
	{
		tab->buff->next = ft_memalloc_exit(sizeof(t_buffer));
		tab->buff = tab->buff->next;
	}
	if (trad)
	{
		while(trad[++i])
			tab->buff->reg[tab->buff->index++] = trad[i];
		free(trad);
	}
	else
		tab->buff->reg[tab->buff->index++] = inst;
}

/*
char *trad_instruc(t_pushswap *tab, int inst)
{
	char res[4];


	if ()

}*/

/*reflechir a comment enlever*/

void clean_buffer(t_pushswap *tab, int state)
{
	t_pushswap *res;
	int ind;
	char tmp;

	tab->buff = tab->origine;
	res = ft_memalloc_exit(sizeof(t_pushswap));
	res->buff = ft_memalloc_exit(sizeof(t_buffer));
	res->origine = res->buff;
	while(tab->buff)
	{
		ind = 0;
		while(ind < tab->buff->index)
		{
			tmp = tab->buff->index->reg[i];
			if (tmp / 3  == tab->buff->index->reg[i + 1] / 3 && tmp / 3  < 3)
				fill_buffer(res, 0, trad_instruc(res, tmp + (2 - tmp % 3)));
			//judge_inst(tab->buff->index->reg[i], tab->buff->index->reg[i + 1]);
			i += 2;
		}
		tab->buff = tab->buff->next;
	}
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
		clean_buffer(tab, 0);
		read_buffer(tab);
	}
	return (0);
}
