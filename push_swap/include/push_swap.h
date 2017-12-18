#include "../../libft/include/libft.h"
#include <stdlib.h>
#include <limits.h>

enum {D_ROTATE, ROTATE, SWITCH, PUSH};
enum {RRA, RRB, RRR, RA, RB, RR, SA, SB, SS, PA, RB, PP}

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
  t_buffer *buff;
  t_buffer *origine;
}				t_pushswap;

void fill_buffer(t_pushswap *tab, int inst, char *trad);
void	tri_stack_3(t_pushswap *tab, int size, int cible);
char	*choice_register(int choice, int inst);
void	get_argc_to_tab(t_pushswap *tab, char **arg, long cnt_c, int argc);
void	execute_instruction(t_pushswap *t, int choice, int inst, int rec);
void	get_instruc(t_pushswap *tab, int size, int cible, int fiter);
int		verif_pile(t_pushswap *tab, int size, char sens);
