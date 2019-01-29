/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 13:23:29 by anleclab          #+#    #+#             */
/*   Updated: 2019/01/29 17:32:18 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdlib.h>

static void		init_minmax(t_fdf *fdf)
{
	if (fdf->map_info.proj == TOP)
	{
		XMAX = WIDTH - 1;
		XMIN = 0;
		YMAX = DEPTH - 1;
		YMIN = 0;
	}
	if (fdf->map_info.proj == PARALLEL)
	{
		XMAX = cos(M_PI / 4) * DEPTH;
		XMIN = XMAX;
		YMAX = -(fdf->map[0][0] + sin(M_PI / 4) * DEPTH);
		YMIN = YMAX;
	}
	if (fdf->map_info.proj == ISOMETRIC)
	{
		XMAX = 0;
		XMIN = 0;
		YMAX = -fdf->map[0][0] * WIDTH / 2;
		YMIN = YMAX;
	}
}

static void	top_projection(t_fdf *fdf)
{
	int		i;
	int		j;

	i = -1;
	while (++i < DEPTH)
	{
		j = -1;
		while (++j < WIDTH)
		{
			fdf->proj_map[i][j].x = j;
			fdf->proj_map[i][j].y = i;
		}
	}
}

static void	parallel_projection(t_fdf *fdf)
{
	int		i;
	int		j;

	i = -1;
	while (++i < DEPTH)
	{
		j = -1;
		while (++j < WIDTH)
		{
			if ((fdf->proj_map[i][j].x = j + cos(M_PI / 4) * (DEPTH - i)) > XMAX)
				XMAX = fdf->proj_map[i][j].x;
			XMIN = (fdf->proj_map[i][j].x < XMIN) ? fdf->proj_map[i][j].x : XMIN;
			if ((fdf->proj_map[i][j].y = -(fdf->map[i][j] * fdf->map_info.alt_ratio + sin(M_PI / 4)
							* (DEPTH - i))) > YMAX)
				YMAX = fdf->proj_map[i][j].y;
			YMIN = (fdf->proj_map[i][j].y < YMIN) ? fdf->proj_map[i][j].y : YMIN;
		}
	}
}

static void	isometric_projection(t_fdf *fdf)
{
	int		i;
	int		j;

	i = -1;
	while (++i < DEPTH)
	{
		j = -1;
		while (++j < WIDTH)
		{
			if ((fdf->proj_map[i][j].x = (i + j) * cos(M_PI / 6) * DEPTH / 2) > XMAX)
				XMAX = fdf->proj_map[i][j].x;
			XMIN = (fdf->proj_map[i][j].x < XMIN) ? fdf->proj_map[i][j].x : XMIN;
			if ((fdf->proj_map[i][j].y = (i - j) * sin(M_PI / 6) * WIDTH / 2 - fdf->map[i][j]
						* WIDTH / 2 * fdf->map_info.alt_ratio) > YMAX)
				YMAX = fdf->proj_map[i][j].y;
			YMIN = (fdf->proj_map[i][j].y < YMIN) ? fdf->proj_map[i][j].y : YMIN;
		}
	}
}

int			projection(t_fdf *fdf)
{
	init_minmax(fdf);
	if (PROJ == TOP)
		top_projection(fdf);
	else if (PROJ == ISOMETRIC)
		isometric_projection(fdf);
	else if (PROJ == PARALLEL)
		parallel_projection(fdf);
	else
		return (0);
	return (1);
}
