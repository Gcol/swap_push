/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 19:24:07 by gcollett          #+#    #+#             */
/*   Updated: 2017/12/18 19:28:53 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../../libft/include/libft.h"
# include <stdlib.h>
# include <limits.h>

enum {EMPTY, D_ROTATE, ROTATE, PUSH, SWITCH};

typedef struct	s_buffer
{
	size_t			index;
	char			reg[500];
	struct s_buffer	*next;
}				t_buffer;

typedef struct	s_pushswap
{
	t_dlist		*stack_a;
	t_dlist		*stack_b;
	t_buffer	*registre;
	t_buffer	*origine;
}				t_pushswap;

int				verif_pile(t_pushswap *tab, int size, char sens);
char			*choice_register(int choice, int inst);
void			fill_buffer(t_buffer **registre, char dta, char *data);
void			tri_stack_3(t_pushswap *tab, int size, int cible);
void			execute_instruction(t_pushswap *t, int choice, char inst);
void			get_instruc(t_pushswap *tab, int size, int cible, int fiter);
void			get_argc_to_tab(t_pushswap *tab, char **ag, long cnt, int argc);
void			little_tri(t_pushswap *tab, char size);
void tri5(t_pushswap *tab, char size);

#endif
