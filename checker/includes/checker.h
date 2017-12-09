#include <libft.h>

enum {PUSH, D_ROTATE, ROTATE, SWITCH};

typedef struct	s_pushswap
{
  t_dlist *stack_A;
  t_dlist *stack_B;
  int    nb_registre;
}				t_pushswap;
