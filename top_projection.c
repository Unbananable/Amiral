/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   top_projection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 16:23:19 by anleclab          #+#    #+#             */
/*   Updated: 2019/01/18 18:07:56 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

t_point	**top_projection(int **map, t_map *map_info)
{
	t_point	**res;
	int		i;
	int		j;

	map += 0;
	if (!(res = (t_point **)malloc(sizeof(t_point *) * map_info->depth)))
		error("MALLOC TU PUES");
	i = -1;
	while (++i < map_info->depth)
	{
		if (!(res[i] = (t_point *)malloc(sizeof(t_point) * map_info->width)))
			error("ET TU MALLOC");
		j = -1;
		while (++j < map_info->width)
		{
			res[i][j].x = j;
			res[i][j].y = i;
		}
	}
	map_info->xmax = map_info->width - 1;
	map_info->ymax = map_info->depth - 1;
	return (res);
}
