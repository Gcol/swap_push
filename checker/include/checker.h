
#include "../../libft/include/libft.h"
#include <stdarg.h>
#include <fcntl.h>

enum {PUSH, D_ROTATE, ROTATE, SWITCH};

typedef struct	s_pushswap
{
  t_dlist *stack_A;
  t_dlist *stack_B;
  int    nb_registre;
}				t_pushswap;

t_dlist	*add_st(char *str, t_dlist *stack, t_dlist *res);
void get_argc_to_tab(t_pushswap *tab, char **arg, long cnt_c, int argc);
void	execute_instruction(t_pushswap *t, int choice, int inst);
void ft_dlist_make_circular(t_dlist *tab);
void launch_instruction(t_pushswap *tab, int len, int choice);
