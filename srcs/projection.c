/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 13:23:29 by anleclab          #+#    #+#             */
/*   Updated: 2019/02/08 12:27:15 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdlib.h>

static void	init_minmax(t_fdf *fdf)
{
	if (fdf->proj == TOP)
	{
		fdf->xmax = fdf->width - 1;
		fdf->xmin = 0;
		fdf->ymax = fdf->depth - 1;
		fdf->ymin = 0;
	}
	if (fdf->proj_type == PARALLEL)
	{
		fdf->xmax = cos(M_PI / 4) * DEPTH;
		fdf->xmin = fdf->xmax;
		fdf->ymax = -(fdf->map[0][0] + sin(M_PI / 4) * DEPTH);
		YMIN = YMAX;
	}
	if (fdf->proj_type == ISOMETRIC)
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
			calc_top(fdf, i, j);
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
			calc_para(fdf, i, j);
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
			calc_iso(fdf, i, j);
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
