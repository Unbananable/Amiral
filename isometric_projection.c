/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric_projection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 19:03:06 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/01/24 18:55:20 by dtrigalo         ###   ########.fr       */
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
			if ((res[i][j].x = 1 + (i + j) * cos(M_PI / 6)) > XMAX)
				XMAX = res[i][j].x;
			//XMIN = (res[i][j].x <			 XMIN) ? res[i][j].x : XMIN;
			if ((res[i][j].y = 1 + (i - j) * -sin(M_PI / 6) + map[i][j]) > YMAX)
				YMAX = res[i][j].y;
			//YMIN = (res[							i][j].y < YMIN) ? res[i][j].y : YMIN;
		}
	}
	return (res);
}
