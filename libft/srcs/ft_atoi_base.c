/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 10:20:45 by anleclab          #+#    #+#             */
/*   Updated: 2019/02/01 10:34:32 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi_base(char *nbr, int base)
{
	int		res;
	int		i;
	int		pow;
	int		tmp;

	if (base > 16)
		return (-1);
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
		if (tmp >= base)
			return (-1);
		res += tmp * pow;
		pow *= base;
	}
	return (res);
}
