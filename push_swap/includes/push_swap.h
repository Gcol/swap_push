#include <libft.h>
#include <stdlib.h>

enum {D_ROTATE, PUSH, ROTATE, SWITCH};

typedef struct	s_buffer
{
  size_t  index;
  char reg[500];
  struct s_buffer *next;
}				t_buffer;

typedef struct	s_pushswap
{
  t_dlist *stack_A;
  t_dlist *stack_B;
  t_buffer *registre;
  t_buffer *origine;
}				t_pushswap;

long ***parser_swap(char **argv, int argc);
int str_is_valid(char **format, char *str, char *first_carac);
