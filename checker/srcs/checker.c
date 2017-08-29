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
#include <fcntl.h>

#include <stdio.h>

void	ft_print_tab(long *tab, long taille)
{
	long i;

	i = 0;
	while(i < taille)
	{
		printf("%ld | ", tab[i]);
		i++;
	}
	printf("\n");
	printf("taille = %ld\n", taille);
}

void double_rotate(long ***tab, int choice)
{
	long target;
	long tmp;
	long i;

	if (choice > 1 && (choice = 1))
		double_rotate(tab, 0);
	if (tab[choice][1][0])
	{
			i = tab[choice][1][0] - 1;
			target = tab[choice][0][tab[choice][1][0] - 1];
			while(--i >= 0)
			{
				printf("%ld <- %ld | taille = %ld \n", 	tab[choice][0][i], tab[choice][0][i + 1], tab[0][1][0]);
				tmp = tab[choice][0][i];
				tab[choice][0][i] = target;
				tab[choice][0][i + 1] = tmp;
			}
			ft_print_tab(tab[choice][0], tab[choice][1][0]);
		}
}

void	execute_instruction(long ***tab, int choice, long coord)
{
	long target;
	long tmp;
	long i;

	printf("choice = %d |  coord = %ld \n", choice, coord);
	if (choice > 1 && (choice = 1))
		execute_instruction(tab, 0, coord);
	i =  1;
	if (coord == 1)
		coord = tab[choice][1][0];
	target = tab[choice][0][0];
	while(i < tab[choice][1][0] && i != coord)
	{
		printf("%ld <- %ld | taille = %ld \n", 	tab[choice][0][i], tab[choice][0][i - 1], tab[0][1][0]);
		tmp = tab[choice][0][i];
		tab[choice][0][i] = target;
		tab[choice][0][i - 1] = tmp;
		i += 1;
	}
	ft_print_tab(tab[choice][0], tab[choice][1][0]);
}

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
	printf("taille = %ld\n", taille);
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

void push_instruction(long ***tab, int choice)
{
	long	*tmp;
	long	i;

	i = 0;
	if (tab[-choice + 1][1][0])
	{
		tmp = ft_memalloc_exit(((tab[choice][1][0]) + 1) * sizeof(long));
		while(++i < tab[choice][1][0] + 1)
			tmp[i] = tab[choice][0][i - 1];
		tmp[0] = tab[-choice + 1][0][0];
		free(tab[choice][0]);
		tab[choice][0] = tmp;
		tab[choice][1][0] += 1;
		i = 0;
		tmp = ft_memalloc_exit((tab[-choice + 1][1][0] - 1) * sizeof(long));
		while(++i < tab[-choice + 1][1][0])
			tmp[i - 1] = tab[-choice + 1][0][i];
		free(tab[-choice + 1][0]);
		tab[-choice + 1][0] = tmp;
		tab[-choice + 1][1][0] -= 1;
	}
}

int	launch_instruction(char *str, long ***tab)
{
	long len;
	int choice;

	choice = 4;
	len = ft_strlen(str);
	if (len == 2 || len == 3)
	{
		if (str[0] == str[1] && str[1] == str[len -1] && ft_c_in_str(str[0], "rps"))
			choice = 3;
		if (str[len - 1] == 'a' || str[len - 1] == 'b')
			choice = str[len - 1] - 'a';
		if (str[0] == 's')
			execute_instruction(tab, choice, 2);
		else if (str[0] == 'p' && choice < 2)
			push_instruction(tab, choice);
		else if (str[0] == 'r' && len == 2)
			execute_instruction(tab, choice, 1);
		else if (str[0] == 'r' && len == 3)
			double_rotate(tab, choice);
	}
	printf("choice = %d | str = %s\n",choice, str );
	free(str);
	return (choice);
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

int main(int argc, char **argv)
{
	long ***tab;
	char *str;
	int error;
	int	fd;

 	error = 1;
	if (argc > 1)
	{
		if (str_is_valid(argv + 1, "0123456789", '-') && !(error = 0))
		{
			tab = ft_memalloc_exit(sizeof(long **) * 2);
			fd = open(0, O_RDONLY);
			tab[0] = parsing_to_longlong(argv + 1, argc - 1);
			if (!longlong_check_rep(*tab[0], argc - 1))
				error = 1;
			ft_print_tab(tab[0][0], tab[0][1][0]);
			tab[1] = ft_memalloc_exit(sizeof(long *) * 2);
			tab[1][0] = ft_memalloc_exit(1 * sizeof(long));
			tab[1][1] = ft_memalloc_exit(1 * sizeof(long));
			while(error == 0 && get_next_line(0, &str))
			{
				if (launch_instruction(str, tab) == 4)
					error = 1;
			}
		}
	}
	if (error != 0)
		write(1, "Error\n", 7);
	return (1);
}
