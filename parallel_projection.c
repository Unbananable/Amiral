/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallel_projection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 18:17:01 by anleclab          #+#    #+#             */
/*   Updated: 2019/01/18 17:56:59 by anleclab         ###   ########.fr       */
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
			res[i][j].x = nearbyint(i + ratio * cos(angle) * (map_info->depth - i));
			res[i][j].y = nearbyint(map[i][j] + ratio * sin(angle) * (map_info->depth - i));
		}
	}
	return (res);
}
