/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_len.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 23:56:54 by gcollett          #+#    #+#             */
/*   Updated: 2017/12/12 23:57:26 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_dlist_len(t_dlist *lst)
{
	t_dlist	*tmp;
	size_t	i;

	i = 1;
	tmp = lst->next;
	while (tmp != NULL && tmp != lst && ++i)
		tmp = tmp->next;
	return (i);
}
