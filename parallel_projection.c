/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallel_projection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 18:17:01 by anleclab          #+#    #+#             */
/*   Updated: 2019/01/18 10:44:30 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* TO DO
 * - gestion des erreurs (fuites memoire etc.)
 * - formules de calcul des coordonnees (cf cahier)
*/

#include <math.h>

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
		while (++(i.x) < map_info->length)
		{
			if ((res[i.y][i.x].x = (int)nearbyint((i.y + ratio * cos(angle) * (map_info->depth - i.y)) * map_info->scale) > map_info->x_max))
				map_info->x_max = res[i.y][i.x].x;
			if ((res[i.y][i.x].y = (int)nearbyint((map[i.y][i.x] + ratio * sin(angle) * (map_info->dept - i.y)) * map_info->scale) > map_info->y_max))
				map_info->y_max = res[i.y][i.x].y;
		}
	}
}
