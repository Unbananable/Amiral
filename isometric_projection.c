/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric_projection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 19:03:06 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/01/21 15:11:42 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "fdf.h"

t_point			**isometric_projection(int **map, t_map *map_info)
{
	int		i;
	int		j;
	t_point	**res;

	if (!(res = (t_point **)malloc(sizeof(t_point *) * map_info->depth)))
		error("Askip c'est MALLOC TOUT PETE");
	i = -1;
	while (++i < map_info->depth)
	{
		if (!(res[i] = (t_point *)malloc(sizeof(t_point) * map_info->width)))
			error("Askip c'est un SACRE MALLOC !");
		j = -1;
		while (++j < map_info->width)
		{
			if ((res[i][j].x = (i - j) * cos(M_PI / 6)) > map_info->xmax)
				map_info->xmax = res[i][j].x;
			if ((res[i][j].y = (i + j) * sin(M_PI / 6) - map[i][j]) > map_info->ymax)
				map_info->ymax = res[i][j].y;
		}
	}
	return (res);
}
