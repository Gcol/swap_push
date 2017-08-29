/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_factory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/14 15:11:27 by gcollett          #+#    #+#             */
/*   Updated: 2017/07/14 15:11:29 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

void ft_malloc_factory(int nb, ...)
{
  va_list lst;
  int index;
  int taille;
  char **s;

  index = 0;
  va_start(lst, nb);
  while(index < nb)
  {
      taille = va_arg(lst, int);
      s = va_arg(lst, char **);
      if (!(s = malloc(taille)))
      {
        va_end(lst);
        exit(0);
      }
      index++;
  }
  va_end(lst);
}
