/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 11:54:06 by anleclab          #+#    #+#             */
/*   Updated: 2019/02/08 14:49:46 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "keys.h"

int		is_valid_mapchar(char c)
{
	if (c == '-' || c == ',' || (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F')
			|| (c >= 'a' && c <= 'f') || c == 'x' || c == 'X' || c == '\n'
			|| c == ' ' || c == '\t')
		return (1);
	return (0);
}

t_ipos	get_ipos(int i, int j)
{
	t_ipos	res;

	res.i = i;
	res.j = j;
	return (res);
}

void	alt_and_move(int key, t_fdf *fdf)
{
	if (key == UP_ARROW || key == DOWN_ARROW)
		event_adjust_alt(key, &(fdf->alt_ratio));
	else
		event_move(key, fdf);
	if (!(projection(fdf)))
		error("error: failed to update projection", fdf);
}
