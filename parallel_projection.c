/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallel_projection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 18:17:01 by anleclab          #+#    #+#             */
/*   Updated: 2019/01/18 18:48:38 by anleclab         ###   ########.fr       */
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
	int		i;
	int		j;

	angle = 45.0;
	ratio = 1.0;
	if (!(res = (t_point **)malloc(sizeof(t_point *) * map_info->depth)))
		error("MALLOC TOUT PETE");
	i = -1;
	while (++i < map_info->depth)
	{
		if (!(res[i] = (t_point *)malloc(sizeof(t_point) * map_info->width)))
			error("SACRE MALLOC !");
		j = -1;
		while (++j < map_info->width)
		{
			if ((res[i][j].x = j + ratio * cos(angle) * (map_info->depth - i)) > map_info->xmax)
				map_info->xmax = res[i][j].x;
			if ((res[i][j].y = map_info->depth - map[i][j] - ratio * sin(angle) * (map_info->depth - i)) > map_info->ymax)
				map_info->ymax = res[i][j].y;
		}
	}
	return (res);
}
