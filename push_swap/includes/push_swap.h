#include <libft.h>
#include <stdlib.h>

enum {D_ROTATE, PUSH, ROTATE, SWITCH};

typedef struct	s_pushswap
{
  t_dlist *stack_A;
  t_dlist *stack_B;
  char  *res;
}				t_pushswap;


long ***parser_swap(char **argv, int argc);
int str_is_valid(char **format, char *str, char *first_carac);
