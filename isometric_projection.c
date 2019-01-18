/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric_projection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 19:03:06 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/01/18 14:20:42 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "fdf.h"

static t_point	iso(double x, double y, double z)
{
	t_point	point;

	point.x = (x - y) * cos(M_PI / 6);
	point.y = (x + y) * sin(M_PI / 6);
	return (point);
}

t_point			**isometric_projection(int **map, t_map *map_info)
{
	int		i;
	int		j;
	t_point	**res;

	if (!(res = (t_point **)malloc(sizeof(t_point *) * map_info->depth)))
		error("Askip c'est MALLOC TOUT PETE");
	i = 0;
	while (i < map_info->depth)
	{
		if (!(res[i] = (t_point *)malloc(sizeof(t_point) * map_info->width)))
			error("Askip c'est un SACRE MALLOC !");
		j = 0;
		while (j < map_info->width)
		{
			res[i][j].x = iso(i, j, map[i][j]).x * map_info->scale;
			res[i][j].y = iso(i, j, map[i][j]).y * map_info->scale;
			if (res[i][j].x > map_info->xmax)
				map_info->xmax = res[i][j].x;
			if (res[i][j].y > map_info->ymax)
				map_info->ymax = res[i][j].y;
			j++;
		}
		i++;
	}
	return (res);
}
