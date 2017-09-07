/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 05:34:50 by gcollett          #+#    #+#             */
/*   Updated: 2017/08/28 20:16:08 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <libft.h>
#include <checker.h>
#include <fcntl.h>

#include <stdio.h>

void verif_pile(long ***tab)
{
 int error;
 int i;
 int sens;

 sens = 0;
 error = 1;
 i = 0;
 if (!tab[1][1][0])
 {
	 error = 0;
	 while(i < tab[0][1][0] - 1)
	 {
		 if (!sens && tab[0][0][i] != tab[0][0][i + 1])
			 sens = (tab[0][0][i] < tab[0][0][i + 1]) ? 1 : -1;
		 if (tab[0][0][i] < tab[0][0][i + 1] && sens == -1)
			 error = 1;
		 else if (tab[0][0][i] > tab[0][0][i + 1] && sens == 1)
			 error = 1;
		 i++;
	 }
 }
 if (error != 0)
	 write(1, "Erreur de tri\n", 14);
 else
	 write(1, "Ok\n", 3);
}

int main(int argc, char **argv)
{
	long ***tab;
	char *str;
	int error;

 	error = 1;
	if (argc > 1)
	{
		if (str_is_valid(argv + 1, "0123456789", "+-") && !(error = 0))
		{
			tab =  parser_swap(argv + 1, argc - 1);
			while(error == 0 && get_next_line(0, &str) > 0)
			{
				if (launch_instruction(str, tab) == 4)
					error = 1;
			}
			verif_pile(tab);
		}
	}
	return (1);
}
