/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 20:18:08 by gcollett          #+#    #+#             */
/*   Updated: 2017/12/12 23:59:47 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static char	ft_atoll2(char nb)
{
	if (nb == '-')
		return ('n');
	if (nb == '+')
		return ('p');
	else
		return ('a');
}

long		ft_atoll(char *nb)
{
	int			a;
	char		c;
	long long	ret;

	a = 0;
	ret = 0;
	while ((nb[a] >= 8 && nb[a] <= 13) || nb[a] == 32)
		a++;
	if ('a' < (c = ft_atoll2(nb[a])))
		a++;
	while (nb[a] > 47 && nb[a] < 58 &&
			((ret * -10 - (long)(nb[a] - '0')) > LLONG_MIN))
		ret = ret * 10 + (nb[a++] - '0');
	if (nb[a] > 47 && nb[a] < 58 &&
			(ret * -10 - (nb[a] - '0')) == LLONG_MIN && c == 'n')
		return (LLONG_MIN);
	else if ((nb[a] < 48 || nb[a] > 57) && c != 'n')
		return (ret);
	else if ((nb[a] < 48 || nb[a] > 57) && c == 'n')
		return (-ret);
	return (0);
}
