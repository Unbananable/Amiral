/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 10:49:11 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/01/13 12:32:03 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_int_array(int *array, int arr_size)
{
	int	i;

	i = -1;
	if (arr_size > 0)
		ft_putchar('[');
	while (++i < arr_size)
	{
		ft_putnbr(array[i]);
		(i + 1 == arr_size) ? ft_putstr("]\n") : ft_putstr(", ");
	}
}
