/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallel_projection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 18:17:01 by anleclab          #+#    #+#             */
/*   Updated: 2019/01/18 12:38:00 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* TO DO
 * - gestion des erreurs (fuites memoire etc.)
*/

#include <math.h>
#include "fdf.h"
#include <stdlib.h>

t_point	**parallel_projection(int **map, t_map *map_info)
{
	t_point	**res;
	double	angle;
	double	ratio;
	t_point	i;

	angle = 45.0;
	ratio = 1.0;
	if (!(res = (t_point **)malloc(sizeof(t_point *) * map_info->depth)))
		error("MALLOC TOUT PETE");
	i.y = -1;
	while (++(i.y) < map_info->depth)
	{
		if (!(res[i.y] = (t_point *)malloc(sizeof(t_point) * map_info->width)))
			error("SACRE MALLOC !");
		i.x = -1;
		while (++(i.x) < map_info->width)
		{
			if ((res[i.y][i.x].x = (int)nearbyint((i.y + ratio * cos(angle) * (map_info->depth - i.y)) * map_info->scale) > map_info->xmax))
				map_info->xmax = res[i.y][i.x].x;
			if ((res[i.y][i.x].y = (int)nearbyint((map[i.y][i.x] + ratio * sin(angle) * (map_info->depth - i.y)) * map_info->scale) > map_info->ymax))
				map_info->ymax = res[i.y][i.x].y;
		}
	}
	return (res);
}
