#include "libft.h"

void  ft_exit(long motif)
{
  if (motif == 2 || motif < 2 || motif > 2)
    write(2, "Error\n", 6);
  exit(motif);
}
