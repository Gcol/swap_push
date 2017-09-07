/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 15:08:36 by gcollett          #+#    #+#             */
/*   Updated: 2017/09/07 15:08:43 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

int	main(int argc, char **argv)
{
	long ***tab;

	if (argc > 1)
	{
		if (str_is_valid(argv + 1, "0123456789", "+-"))
		{
			tab = parser_swap(argv + 1, argc - 1);
		}
	}
	else
		write(1, "Usage : ./push_swap [number]\n", 29);
	return (0);
}
