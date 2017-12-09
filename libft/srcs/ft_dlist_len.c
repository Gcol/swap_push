#include "libft.h"

size_t  ft_dlist_len(t_dlist *lst)
{
  t_dlist *tmp;
  size_t  i;

  i = 0;
  tmp = lst;
  while(tmp->next != NULL && tmp->next != lst)
  {
    tmp = tmp->next;
    i++;
  }
  return (i);
}
