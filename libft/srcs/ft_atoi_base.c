/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 10:20:45 by anleclab          #+#    #+#             */
/*   Updated: 2019/02/07 17:37:14 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_right_base(int base)
{
	if (base < 2 || base > 16)
		return (0);
	return (1);
}

int			ft_atoi_base(char *nbr, int base)
{
	int		res;
	int		i;
	int		pow;
	int		tmp;

	res = 0;
	pow = 1;
	i = ft_strlen(nbr);
	while (--i >= 0)
	{
		if (nbr[i] >= '0' && nbr[i] <= '9')
			tmp = nbr[i] - '0';
		else if (nbr[i] >= 'A' && nbr[i] <= 'F')
			tmp = nbr[i] - 'A' + 10;
		else if (nbr[i] >= 'a' && nbr[i] <= 'f')
			tmp = nbr[i] - 'a' + 10;
		else
			return (-1);
		if (tmp >= base || !is_right_base(base))
			return (-1);
		res += tmp * pow;
		pow *= base;
	}
	return (res);
}
