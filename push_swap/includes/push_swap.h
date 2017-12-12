#include <libft.h>
#include <stdlib.h>


enum {PUSH, D_ROTATE, ROTATE, SWITCH};

typedef struct	s_pushswap
{
  t_dlist *stack_A;
  t_dlist *stack_B;
  char  *registre;
}				t_pushswap;


long ***parser_swap(char **argv, int argc);
int str_is_valid(char **format, char *str, char *first_carac);
