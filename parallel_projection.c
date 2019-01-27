/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallel_projection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 18:17:01 by anleclab          #+#    #+#             */
/*   Updated: 2019/01/27 15:49:55 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	angle = M_PI / 4;
	ratio = 1.0;
	XMAX = ratio *cos(angle) * DEPTH;
	XMIN = XMAX;
	YMAX = -(map[0][0]+ ratio * sin(angle) * DEPTH);
	YMIN = YMAX;
	if (!(res = (t_point **)malloc(sizeof(t_point *) * DEPTH)))
		error("MALLOC TOUT PETE");
	i = -1;
	while (++i < DEPTH)
	{
		if (!(res[i] = (t_point *)malloc(sizeof(t_point) * WIDTH)))
			error("SACRE MALLOC !");
		j = -1;
		while (++j < WIDTH)
		{
			if ((res[i][j].x = j + ratio * cos(angle) * (DEPTH - i)) > XMAX)
				XMAX = res[i][j].x;
			XMIN = (res[i][j].x < XMIN) ? res[i][j].x : XMIN;
			if ((res[i][j].y = -(map[i][j] + ratio * sin(angle) * (DEPTH - i))) > YMAX)
				YMAX = res[i][j].y;
			YMIN = (res[i][j].y < YMIN) ? res[i][j].y : YMIN;
		}
	}
	return (res);
}
