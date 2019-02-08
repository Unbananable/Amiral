/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_calculus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:38:14 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/02/08 14:11:29 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	calc_para(t_fdf *fdf, int i, int j)
{
	double	x;
	double	y;
	double	z;

	x = i;
	y = j;
	z = fdf->map[i][j];
	fdf->proj[i][j].z = fdf->map[i][j];
	rotate_x(&y, &z, fdf->alpha);
	rotate_y(&x, &z, fdf->beta);
	rotate_z(&x, &y, fdf->gamma);
	if ((fdf->proj[i][j].x = y + cos(M_PI / 4) * (fdf->depth - x)) > fdf->xmax)
		fdf->xmax = fdf->proj[i][j].x;
	fdf->xmin = (fdf->proj[i][j].x < fdf->xmin) ? fdf->proj[i][j].x : fdf->xmin;
	if ((fdf->proj[i][j].y = -(z * fdf->alt_ratio + sin(M_PI / 4)
					* (fdf->depth - x))) > fdf->ymax)
		fdf->ymax = fdf->proj[i][j].y;
	fdf->ymin = (fdf->proj[i][j].y < fdf->ymin) ? fdf->proj[i][j].y : fdf->ymin;
}

void	calc_iso(t_fdf *fdf, int i, int j)
{
	double	x;
	double	y;
	double	z;

	x = i;
	y = j;
	z = fdf->map[i][j];
	fdf->proj[i][j].z = fdf->map[i][j];
	rotate_x(&y, &z, fdf->alpha);
	rotate_y(&x, &z, fdf->beta);
	rotate_z(&x, &y, fdf->gamma);
	if ((fdf->proj[i][j].x = (x + y) * cos(M_PI / 6) * fdf->depth / 2)
			> fdf->xmax)
		fdf->xmax = fdf->proj[i][j].x;
	fdf->xmin = (fdf->proj[i][j].x < fdf->xmin) ? fdf->proj[i][j].x : fdf->xmin;
	if ((fdf->proj[i][j].y = (x - y) * sin(M_PI / 6) * fdf->width / 2 - z
				* fdf->width / 2 * fdf->alt_ratio) > fdf->ymax)
		fdf->ymax = fdf->proj[i][j].y;
	fdf->ymin = (fdf->proj[i][j].y < fdf->ymin) ? fdf->proj[i][j].y : fdf->ymin;
}

void	calc_top(t_fdf *fdf, int i, int j)
{
	double	x;
	double	y;
	double	z;

	x = i;
	y = j;
	z = fdf->map[i][j];
	fdf->proj[i][j].z = fdf->map[i][j];
	rotate_x(&y, &z, fdf->alpha);
	rotate_y(&x, &z, fdf->beta);
	rotate_z(&x, &y, fdf->gamma);
	fdf->proj[i][j].x = y;
	fdf->proj[i][j].y = x;
}
