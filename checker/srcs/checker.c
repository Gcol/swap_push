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

long **parsing_to_longlong(char **format, long taille)
{
	long index;
	long **result;

 	index = 0;
	result = ft_memalloc_exit((sizeof(long *) * 2));
	result[0] = ft_memalloc_exit((taille + 1) * sizeof(long));
	result[1] = ft_memalloc_exit(1);
	while(index < taille)
	{
		result[0][index] = ft_atoll(format[index]);
		index++;
	}
	result[1][0] = taille;
	return(result);
}

int longlong_check_rep(long *src, int len)
{
	long	*tmp;
	char	diff;
	long	i;
	long	j;

	i = 0;
	diff = 1;
	tmp = ft_memalloc_exit(len * sizeof(long));
	while(i < len && diff == 1)
	{
		j = 1;
		while(j < i)
		{
			if (tmp[j] == src[i])
				diff = 0;
			j++;
		}
		tmp[i] = src[i];
		i++;
	}
	free(tmp);
	return (diff);
}

int str_is_valid(char **format, char *str, char first_carac)
{
	long	index_f;
	long	index_format;

	index_f = 0;
	index_format = 0;
	while (format[index_format])
	{
		while (format[index_format][index_f])
		{
			if (format[index_format][index_f] == first_carac)
				index_f++;
			if (!ft_c_in_str(format[index_format][index_f], str))
				return (0);
			index_f++;
		}
		index_f = 0;
		index_format++;
	}
	return (1);
}

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
		if (str_is_valid(argv + 1, "0123456789", '-') && !(error = 0))
		{
			tab = ft_memalloc_exit(sizeof(long **) * 2);
			tab[0] = parsing_to_longlong(argv + 1, argc - 1);
			if (!longlong_check_rep(*tab[0], argc - 1))
				error = 1;
			tab[1] = ft_memalloc_exit(sizeof(long *) * 2);
			tab[1][0] = ft_memalloc_exit(1 * sizeof(long));
			tab[1][1] = ft_memalloc_exit(1 * sizeof(long));
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
