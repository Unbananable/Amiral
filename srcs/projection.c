/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 13:23:29 by anleclab          #+#    #+#             */
/*   Updated: 2019/02/08 12:41:12 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdlib.h>

static void	init_minmax(t_fdf *fdf)
{
	if (fdf->proj_type == TOP)
	{
		fdf->xmax = fdf->width - 1;
		fdf->xmin = 0;
		fdf->ymax = fdf->depth - 1;
		fdf->ymin = 0;
	}
	if (fdf->proj_type == PARALLEL)
	{
		fdf->xmax = cos(M_PI / 4) * fdf->depth;
		fdf->xmin = fdf->xmax;
		fdf->ymax = -(fdf->map[0][0] + sin(M_PI / 4) * fdf->depth);
		fdf->ymin = fdf->ymax;
	}
	if (fdf->proj_type == ISOMETRIC)
	{
		fdf->xmax = 0;
		fdf->xmin = 0;
		fdf->ymax = -fdf->map[0][0] * fdf->width / 2;
		fdf->ymin = fdf->ymax;
	}
}

static void	top_projection(t_fdf *fdf)
{
	int		i;
	int		j;

	i = -1;
	while (++i < fdf->depth)
	{
		j = -1;
		while (++j < fdf->depth)
			calc_top(fdf, i, j);
	}
}

static void	parallel_projection(t_fdf *fdf)
{
	int		i;
	int		j;

	i = -1;
	while (++i < fdf->depth)
	{
		j = -1;
		while (++j < fdf->width)
			calc_para(fdf, i, j);
	}
}

static void	isometric_projection(t_fdf *fdf)
{
	int		i;
	int		j;

	i = -1;
	while (++i < fdf->depth)
	{
		j = -1;
		while (++j < fdf->width)
			calc_iso(fdf, i, j);
	}
}

int			projection(t_fdf *fdf)
{
	init_minmax(fdf);
	if (fdf->proj_type == TOP)
		top_projection(fdf);
	else if (fdf->proj_type == ISOMETRIC)
		isometric_projection(fdf);
	else if (fdf->proj_type == PARALLEL)
		parallel_projection(fdf);
	else
		return (0);
	return (1);
}
