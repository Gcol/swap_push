/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 05:34:50 by gcollett          #+#    #+#             */
/*   Updated: 2017/07/13 05:43:59 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <libft.h>
#include <fcntl.h>

void	execute_instruction(int *****tab, int choice, int target, int coord)
{
}

int **parsing_to_int(char **format, int taille)
{
	int index;
	int **result;

 	index = 0;
	result = ft_memalloc_exit((sizeof(int *) * 2));
	result[0] = ft_memalloc_exit((taille + 1) * sizeof(int));
	result[1] = ft_memalloc_exit(1);
	while(index < taille)
	{
		result[0][index] = ft_atoi(format[index]);
		index++;
	}
	result[1][0] = taille;
	return(result);
}

int int_check_rep(int	*src, int len)
{
	int		*tmp;
	int		diff;
	int		i;
	int		j;

	i = 0;
	diff = 1;
	tmp = ft_memalloc_exit(len * sizeof(int));
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

int	launch_instruction(char *str, int ****tab)
{
	int len;
	int choice;

	choice = 4;
	len = ft_strlen(str);
	if (len == 2 || len == 3)
	{
		if (str[0] == str[1] && str[1] == str[len -1] && ft_c_in_str(str[0], "rps"))
			choice = 3;
		if (str[len - 1] == 'a' || str[len - 1] == 'b')
			choice = str[1] - 'a';
		if (str[0] == 's')
			execute_instruction(&tab, choice, *tab[choice][0][0], 1);
		if (str[0] == 'p')
				execute_instruction(&tab, choice, *tab[choice][0][0], 2);
		if (str[0] == 'r' && len == 2)
			execute_instruction(&tab, choice, *tab[choice][0][0], -1);
		if (str[0] == 'r' && len == 3)
			execute_instruction(&tab, choice, *tab[choice][0][*tab[choice][1][0]], 0);
	}
	return (choice);
}
/*
void	ft_print_tab(int *tab, int taille)
{
	printf("%d\n", tab[0]);
	int i;

	i = 0;
	while(tab[i])
	{
		printf("%d | ", tab[i]);
		i++;
	}
}*/

int str_is_valid(char **format, char *str, char first_carac)
{
	int	index_f;
	int index_format;

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

int main(int argc, char **argv)
{
	int ***tab;
	char *str;
	int error;
	int	fd;

 	error = 1;
	if (argc > 1)
	{
		if (str_is_valid(argv + 1, "0123456789", '-') && !(error = 0))
		{
			tab =  ft_memalloc_exit(sizeof(int **) * 2);
			fd = open(0, O_RDONLY);
			tab[0] = parsing_to_int(argv + 1, argc - 1);
			if (!int_check_rep(*tab[0], argc - 1))
				error = 1;
			tab[1] = ft_memalloc_exit(sizeof(int *) * 2);
			tab[1][2] = ft_memalloc_exit(1);
			while(get_next_line(fd, &str) && error == 0)
			{
				if (launch_instruction(str, &tab) == 4)
					error = 1;
				free(str);
			}
		}
	}
	if (error != 0)
		write(1, "Error\n", 7);
	return (1);
}
