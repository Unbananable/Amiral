/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 13:23:29 by anleclab          #+#    #+#             */
/*   Updated: 2019/01/29 12:43:25 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdlib.h>

static void		init_minmax(t_map *map_info, int first_value)
{
	if (map_info->proj == TOP)
	{
		XMAX = WIDTH - 1;
		XMIN = 0;
		YMAX = WIDTH - 1;
		YMIN = 0;
	}
	if (map_info->proj == PARALLEL)
	{
		XMAX = cos(M_PI / 4) * DEPTH;
		XMIN = XMAX;
		YMAX = -(first_value + sin(M_PI / 4) * DEPTH);
		YMIN = YMAX;
	}
	if (map_info->proj == ISOMETRIC)
	{
		XMAX = 0;
		XMIN = 0;
		YMAX = -first_value * WIDTH / 2;
		YMIN = YMAX;
	}
}

static t_point	**top_projection(int **map, t_map *map_info)
{
	t_point	**res;
	int		i;
	int		j;

	map += 0;
	if (!(res = (t_point **)malloc(sizeof(t_point *) * DEPTH)))
		return (NULL);
	i = -1;
	while (++i < DEPTH)
	{
		if (!(res[i] = (t_point *)malloc(sizeof(t_point) * WIDTH)))
		{
			free_2D_tpoint_tab(&res, i);
			return (NULL);
		}
		j = -1;
		while (++j < WIDTH)
		{
			res[i][j].x = j;
			res[i][j].y = i;
		}
	}
	return (res);
}

static t_point	**parallel_projection(int **map, t_map *map_info)
{
	t_point	**res;
	int		i;
	int		j;

	if (!(res = (t_point **)malloc(sizeof(t_point *) * DEPTH)))
		return (NULL);
	i = -1;
	while (++i < DEPTH)
	{
		if (!(res[i] = (t_point *)malloc(sizeof(t_point) * WIDTH)))
		{
			free_2D_tpoint_tab(&res, i);
			return (NULL);
		}
		j = -1;
		while (++j < WIDTH)
		{
			if ((res[i][j].x = j + cos(M_PI / 4) * (DEPTH - i)) > XMAX)
				XMAX = res[i][j].x;
			XMIN = (res[i][j].x < XMIN) ? res[i][j].x : XMIN;
			if ((res[i][j].y = -(map[i][j] * map_info->alt_ratio + sin(M_PI / 4)
							* (DEPTH - i))) > YMAX)
				YMAX = res[i][j].y;
			YMIN = (res[i][j].y < YMIN) ? res[i][j].y : YMIN;
		}
	}
	return (res);
}

static t_point	**isometric_projection(int **map, t_map *map_info)
{
	int		i;
	int		j;
	t_point	**res;

	if (!(res = (t_point **)malloc(sizeof(t_point *) * DEPTH)))
		return (NULL);
	i = -1;
	while (++i < DEPTH)
	{
		if (!(res[i] = (t_point *)malloc(sizeof(t_point) * WIDTH)))
		{
			free_2D_tpoint_tab(&res, i);
			return (NULL);
		}
		j = -1;
		while (++j < WIDTH)
		{
			if ((res[i][j].x = (i + j) * cos(M_PI / 6) * DEPTH / 2) > XMAX)
				XMAX = res[i][j].x;
			XMIN = (res[i][j].x < XMIN) ? res[i][j].x : XMIN;
			if ((res[i][j].y = (i - j) * sin(M_PI / 6) * WIDTH / 2 - map[i][j]
						* WIDTH / 2 * map_info->alt_ratio) > YMAX)
				YMAX = res[i][j].y;
			YMIN = (res[i][j].y < YMIN) ? res[i][j].y : YMIN;
		}
	}
	return (res);
}

t_point			**projection(t_proj proj, int **map, t_map *map_info)
{
	map_info->proj = proj;
	init_minmax(map_info, map[0][0]);
	if (proj == TOP)
		return (top_projection(map, map_info));
	else if (proj == ISOMETRIC)
		return (isometric_projection(map, map_info));
	else if (proj == PARALLEL)
		return (parallel_projection(map, map_info));
	return (NULL);
}
