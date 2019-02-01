/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_calculus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:38:14 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/02/01 14:46:39 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	calc_iso(t_fdf *fdf, int i, int j)
{
	double	x;
	double	y;
	double	z;

	x = i;
	y = j;
	z = fdf->map[i][j];
	fdf->proj_map[i][j].z = fdf->map[i][j];
	rotate_x(&x, &z, fdf->map_info.alpha);
	rotate_y(&x, &z, fdf->map_info.beta);
	rotate_z(&x, &y, fdf->map_info.gamma);
	if ((fdf->proj_map[i][j].x = y + cos(M_PI / 4) * (DEPTH - x)) > XMAX)
		XMAX = fdf->proj_map[i][j].x;
	XMIN = (fdf->proj_map[i][j].x < XMIN) ? fdf->proj_map[i][j].x : XMIN;
	if ((fdf->proj_map[i][j].y = -(z * fdf->map_info.alt_ratio + sin(M_PI / 4)
					* (DEPTH - x))) > YMAX)
		YMAX = fdf->proj_map[i][j].y;
	YMIN = (fdf->proj_map[i][j].y < YMIN) ? fdf->proj_map[i][j].y : YMIN;
}

void	calc_para(t_fdf *fdf, int i, int j)
{
	double	x;
	double	y;
	double	z;

	x = i;
	y = j;
	z = fdf->map[i][j];
	fdf->proj_map[i][j].z = fdf->map[i][j];
	rotate_x(&x, &z, fdf->map_info.alpha);
	rotate_y(&x, &z, fdf->map_info.beta);
	rotate_z(&x, &y, fdf->map_info.gamma);
	if ((fdf->proj_map[i][j].x = (x + y) * cos(M_PI / 6) * DEPTH / 2) > XMAX)
		XMAX = fdf->proj_map[i][j].x;
	XMIN = (fdf->proj_map[i][j].x < XMIN) ? fdf->proj_map[i][j].x : XMIN;
	if ((fdf->proj_map[i][j].y = (x - y) * sin(M_PI / 6) * WIDTH / 2 - z
				* WIDTH / 2 * fdf->map_info.alt_ratio) > YMAX)
		YMAX = fdf->proj_map[i][j].y;
	YMIN = (fdf->proj_map[i][j].y < YMIN) ? fdf->proj_map[i][j].y : YMIN;
}