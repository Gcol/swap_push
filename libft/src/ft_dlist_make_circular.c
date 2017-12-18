#include <libft.h>

void ft_dlist_make_circular(t_dlist *tab)
{
  t_dlist *tmp;

  tmp = tab;
  while (tmp && tmp->next)
    tmp = tmp->next;
  tmp->next = tab;
  tab->prev = tmp;
}
