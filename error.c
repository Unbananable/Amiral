/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 12:09:56 by anleclab          #+#    #+#             */
/*   Updated: 2019/01/18 15:30:22 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include <stdlib.h>

void	error(char *str)
{
	ft_putstr(str);
	ft_putchar('\n');
	exit(0);
}
