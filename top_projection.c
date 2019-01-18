/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   top_projection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 16:23:19 by anleclab          #+#    #+#             */
/*   Updated: 2019/01/18 16:29:21 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

t_point	**top_projection(int **map, t_map *map_info)
{
	t_point	**res;
	t_point	i;

	map += 0;
	if (!(res = (t_point **)malloc(sizeof(t_point *) * map_info->depth)))
		error("MALLOC TU PUES");
	i.y = -1;
	while (++(i.y) < map_info->depth)
	{
		if (!(res[i.y] = (t_point *)malloc(sizeof(t_point) * map_info->width)))
			error("ET TU MALLOC");
		i.x = -1;
		while (++(i.x) < map_info->width)
		{
			res[i.y][i.x].x = i.x;
			res[i.y][i.x].y = i.y;
		}
	}
	return (res);
}
