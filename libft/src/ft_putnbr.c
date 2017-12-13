/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 21:51:38 by gcollett          #+#    #+#             */
/*   Updated: 2016/11/09 02:38:26 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	int	j;

	j = 0;
	if (n != -2147483648)
	{
		if (n < 0)
		{
			write(1, "-", 1);
			n = -n;
		}
		if (n >= 10)
		{
			ft_putnbr(n / 10);
			ft_putnbr(n % 10);
		}
		else
		{
			j = n + 48;
			write(1, &j, 1);
		}
	}
	else
		write(1, "-2147483648", 11);
}