/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_make_circular.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 19:04:53 by gcollett          #+#    #+#             */
/*   Updated: 2017/12/18 19:05:29 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_dlist_make_circular(t_dlist *tab)
{
	t_dlist *tmp;

	tmp = tab;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = tab;
	tab->prev = tmp;
}
