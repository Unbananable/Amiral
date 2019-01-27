/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric_projection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 19:03:06 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/01/27 15:38:36 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "fdf.h"

t_point	**isometric_projection(int **map, t_map *map_info)
{
	int		i;
	int		j;
	t_point	**res;

	XMAX = 0;
	XMIN = 0;
	YMAX = -map[0][0] * WIDTH / 2;
	YMIN = YMAX;
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
			if ((res[i][j].x = (i + j) * cos(M_PI / 6) * DEPTH / 2) > XMAX)
				XMAX = res[i][j].x;
			XMIN = (res[i][j].x < XMIN) ? res[i][j].x : XMIN;
			if ((res[i][j].y = (i - j) * sin(M_PI / 6) * WIDTH / 2 - map[i][j] * WIDTH / 2) > YMAX)
				YMAX = res[i][j].y;
			YMIN = (res[i][j].y < YMIN) ? res[i][j].y : YMIN;
		}
	}
	return (res);
}
