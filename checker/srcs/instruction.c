/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 14:58:37 by gcollett          #+#    #+#             */
/*   Updated: 2017/09/07 15:00:38 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	double_rotate(long ***tab, int choice)
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
		while (--i >= 0)
		{
			tmp = tab[choice][0][i];
			tab[choice][0][i] = target;
			tab[choice][0][i + 1] = tmp;
		}
	}
}

void	execute_instruction(long ***tab, int choice, long coord)
{
	long target;
	long tmp;
	long i;

	if (choice > 1 && (choice = 1))
		execute_instruction(tab, 0, coord);
	i = 1;
	if (coord == 1)
		coord = tab[choice][1][0];
	target = tab[choice][0][0];
	while (i < tab[choice][1][0] && i != coord)
	{
		tmp = tab[choice][0][i];
		tab[choice][0][i] = target;
		tab[choice][0][i - 1] = tmp;
		i += 1;
	}
}

void	push_instruction(long ***tab, int choice)
{
	long	*tmp;
	long	i;

	i = 0;
	if (tab[-choice + 1][1][0])
	{
		tmp = ft_memalloc_exit(((tab[choice][1][0]) + 1) * sizeof(long));
		while (++i < tab[choice][1][0] + 1)
			tmp[i] = tab[choice][0][i - 1];
		tmp[0] = tab[-choice + 1][0][0];
		free(tab[choice][0]);
		tab[choice][0] = tmp;
		tab[choice][1][0] += 1;
		i = 0;
		tmp = ft_memalloc_exit((tab[-choice + 1][1][0] - 1) * sizeof(long));
		while (++i < tab[-choice + 1][1][0])
			tmp[i - 1] = tab[-choice + 1][0][i];
		free(tab[-choice + 1][0]);
		tab[-choice + 1][0] = tmp;
		tab[-choice + 1][1][0] -= 1;
	}
}

int		launch_instruction(char *str, long ***tab)
{
	long	len;
	int		choice;

	choice = 4;
	len = ft_strlen(str);
	if (len == 2 || len == 3)
	{
		if (str[0] == str[1] && str[1] == str[len - 1] &&
			ft_c_in_str(str[0], "rps"))
			choice = 3;
		if (str[len - 1] == 'a' || str[len - 1] == 'b')
			choice = str[len - 1] - 'a';
		if (str[0] == 's' && len < 3)
			execute_instruction(tab, choice, 2);
		else if (str[0] == 'p' && choice < 2)
			push_instruction(tab, choice);
		else if (str[0] == 'r' && len == 2)
			execute_instruction(tab, choice, 1);
		else if (str[0] == 'r' && len == 3)
			double_rotate(tab, choice);
		else
			choice = 4;
	}
	free(str);
	return (choice);
}
