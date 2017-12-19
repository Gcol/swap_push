/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 19:14:15 by gcollett          #+#    #+#             */
/*   Updated: 2017/12/18 19:19:22 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include "../../libft/include/libft.h"
# include <stdarg.h>
# include <fcntl.h>

enum {PUSH, D_ROTATE, ROTATE, SWITCH};

typedef	struct	s_pushswap
{
	t_dlist	*stack_a;
	t_dlist	*stack_b;
	int		nb_registre;
}				t_pushswap;

void			ft_dlist_make_circular(t_dlist *tab);
void			execute_instruction(t_pushswap *t, int choice, int inst);
void			launch_instruction(t_pushswap *tab, int len, int choice);
void			get_argc_to_tab(t_pushswap *tab, char **ag, long cnt, int argc);
t_dlist			*add_st(char *str, t_dlist *stack, t_dlist *res);

#endif
