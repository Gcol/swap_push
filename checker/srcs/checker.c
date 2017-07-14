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


int *parsing_to_int(char **format, int taille)
{
	int index;
	int *result;

 	index = 0;
	if (!(result = ft_memalloc((taille + 1) * sizeof(int))))
		exit(0);
	while(index < taille)
	{
		result[index] = ft_atoi(format[index]);
		index++;
	}
	return(result);
}

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

int	execute_instruction(char *str, int ***result)
{
	/*lit et verifie les instruction et aplllique les */
}

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
}

int main(int argc, char **argv)
{
	int *arg;
	char *str;
	int error;
	int i;
	int	fd;

	i = -1;
	error = 1;
	if (argc > 1)
	{
		if (str_is_valid(argv + 1, "0123456789", '-'))
		{
			error = 0;
			fd = open(0, O_RDONLY);
			arg = parsing_to_int(argv + 1, argc - 1);
			while(get_next_line(fd, &str) && error == 0)
			{
				if (!(execute_instruction(str, &result)))
					error = 1;
				free(str);
			}
		}
	}
	if (error != 0)
		write(1, "Error\n", 7);
	return (1);
}
