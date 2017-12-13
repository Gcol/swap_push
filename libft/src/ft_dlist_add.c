/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 23:57:40 by gcollett          #+#    #+#             */
/*   Updated: 2017/12/12 23:58:03 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlist_add(t_dlist **target, int index, int value)
{
	t_dlist	*new;
	int		i;

	i = -1;
	new = ft_memalloc_exit(sizeof(t_dlist));
	while (++i != index && *target && (*target)->next)
		*target = (*target)->next;
	new->dta = value;
	if ((*target) && (*target)->next && (*target)->prev)
	{
		new->next = (*target);
		new->prev = (*target)->prev;
		(*target)->prev->next = new;
		(*target)->prev = new;
	}
	if (!(*target))
		*target = new;
	if (!(*target)->next)
	{
		(*target)->next = new;
		new->prev = *target;
	}
	if (!(*target)->prev && ((*target)->prev = new))
		new->next = *target;
	*target = new;
}
