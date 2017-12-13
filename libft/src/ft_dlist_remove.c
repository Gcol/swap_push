/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_remove.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 23:58:15 by gcollett          #+#    #+#             */
/*   Updated: 2017/12/12 23:58:51 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlist_remove(t_dlist **target, int index)
{
	t_dlist	*tmp;
	int		i;

	i = -1;
	tmp = NULL;
	while (++i != index && *target)
		*target = (*target)->next;
	if ((*target))
	{
		if ((*target)->next && (*target)->next != *target)
			tmp = (*target)->next;
		else if ((*target)->prev && (*target)->next != *target)
			tmp = (*target)->prev;
		if ((*target)->next && (*target)->prev)
			(*target)->prev->next = (*target)->next;
	  else if ((*target)->prev)
			(*target)->prev->next = NULL;
		if ((*target)->next && (*target)->prev)
			(*target)->next->prev = (*target)->prev;
		else if ((*target)->next)
		  (*target)->next->prev = NULL;
		ft_memdel((void**)&(*target));
		(*target) = tmp;
	}
}
