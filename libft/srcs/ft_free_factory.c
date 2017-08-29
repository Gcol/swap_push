/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_factory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 02:47:41 by gcollett          #+#    #+#             */
/*   Updated: 2017/07/10 02:50:47 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "libft.h"

void 	ft_free_factory(int nb, ...)
{
	va_list lst;
	int i;

	va_start(lst, nb);
	i = 0;
	while(i < nb)
	{
		ft_memdel(va_arg(lst, void **));
		i++;
	}
	va_end(lst);
}

void	ft_free_char(char *s1, char *s2, char *s3, char *s4)
{
	free(s1);
	free(s2);
	free(s3);
	free(s4);
}
