/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallel_projection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 18:17:01 by anleclab          #+#    #+#             */
/*   Updated: 2019/01/25 18:58:58 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"
#include <stdlib.h>

t_point	**parallel_projection(int **map, t_map *map_info)
{
	int		i;
	int		j;
	t_point	**res;

	if (!(res = (t_point **)malloc(sizeof(t_point *) * DEPTH)))
		error("Askip c'est MALLOC TOUT PETE");
	i = -1;
	while (++i < DEPTH)
	{
		if (!(res[i] = (t_point *)malloc(sizeof(t_point) * WIDTH)))
			error("Askip c'est un SACRE MALLOC !");
		j = -1;
		while (++j < WIDTH)
		{
			if ((res[i][j].x = (i + j) * cos(M_PI / 4) * DEPTH / 2) > XMAX)
				XMAX = res[i][j].x;
			XMIN = (res[i][j].x < XMIN) ? res[i][j].x : XMIN;
			if ((res[i][j].y = (i - j) * sin(M_PI / 4) * WIDTH / 2 - map[i][j] * WIDTH / 2) > YMAX)
				YMAX = res[i][j].y;
			YMIN = (res[i][j].y < YMIN) ? res[i][j].y : YMIN;
		}
	}
	return (res);
}
