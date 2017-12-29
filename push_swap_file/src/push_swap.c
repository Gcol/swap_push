/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 19:19:52 by gcollett          #+#    #+#             */
/*   Updated: 2017/12/29 15:46:17 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

void	fill_buffer(t_buffer **registre, char dta, char *data)
{
	int i;

	i = -1;
	if ((*registre)->index + ((data) ? 4 : 1) > 500)
	{
		(*registre)->next = ft_memalloc_exit(sizeof(t_buffer));
		(*registre) = (*registre)->next;
	}
	if (data)
	{
		while (data[++i])
			(*registre)->reg[(*registre)->index++] = data[i];
		free(data);
	}
	else
		(*registre)->reg[(*registre)->index++] = dta;
}

void	check_instruction(t_pushswap *tab, t_buffer *res)
{
	size_t		new_index;
	int			tmp_new;
	int			tmp_old;

	new_index = -1;
	while (++new_index < tab->registre->index)
	{
		if (res->index)
			tmp_new = res->reg[res->index - 1];
		else
			tmp_new = res->reg[res->index];
		tmp_old = tab->registre->reg[new_index];
		if (((tmp_new % 10 == ROTATE && tmp_old % 10 == D_ROTATE)
					|| (tmp_new % 10 == D_ROTATE && tmp_old % 10 == ROTATE)
					|| (tmp_new == PUSH && tmp_old == 10 + PUSH)
					|| (tmp_new == 10 + PUSH && tmp_old == PUSH)) && res->index)
			res->index--;
		else
		{
			if (tmp_new < 20 && tmp_new % 10 == tmp_old % 10
				&& tmp_new != tmp_old)
				tmp_old = tmp_old % 10 + 20;
			fill_buffer(&res, tmp_old, NULL);
		}
	}
}

void	clean_buffer(t_pushswap *tab)
{
	t_buffer	*res;
	t_buffer	*origine;

	res = ft_memalloc_exit(sizeof(t_buffer));
	origine = res;
	tab->registre = tab->origine;
	while (tab->registre)
	{
		check_instruction(tab, res);
		tab->registre = tab->registre->next;
		free(tab->origine);
		tab->origine = tab->registre;
	}
	tab->origine = origine;
}

void	read_buffer(t_buffer *buff)
{
	t_buffer	*affichage;
	t_buffer	*origine;
	t_buffer	*tmp;
	size_t		index;

	tmp = buff;
	affichage = ft_memalloc_exit(sizeof(t_buffer));
	origine = affichage;
	while (tmp)
	{
		index = -1;
		while (++index < tmp->index)
			fill_buffer(&affichage, 0, choice_register(tmp->reg[index]
						/ 10, tmp->reg[index] % 10));
		tmp = tmp->next;
	}
	tmp = origine;
	while (tmp)
	{
		write(1, tmp->reg, tmp->index);
		tmp = tmp->next;
		free(origine);
		origine = tmp;
	}
}

int		main(int argc, char **argv)
{
	t_pushswap	*tab;
	size_t		size;

	if (argc > 1)
	{
		tab = ft_memalloc_exit(sizeof(t_pushswap));
		tab->registre = ft_memalloc_exit(sizeof(t_buffer));
		tab->origine = tab->registre;
		get_argc_to_tab(tab, argv, -1, argc);
		ft_dlist_make_circular(tab->stack_a);
		size = ft_dlist_len(tab->stack_a);
		if (size <= 3)
			little_tri(tab, size);
		else if (size <= 5)
			tri5(tab, size);
		else
			get_instruc(tab, ft_dlist_len(tab->stack_a), 0, 1);
		clean_buffer(tab);
		read_buffer(tab->origine);
	}
	return (0);
}
