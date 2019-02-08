/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:13:13 by anleclab          #+#    #+#             */
/*   Updated: 2019/02/08 14:16:52 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "colors.h"

static int	z_gradient(double ratio, int start_col, int end_col)
{
	int		red;
	int		green;
	int		blue;

	red = color_lvl((start_col >> 16) & 0xFF, (end_col >> 16) & 0xFF, ratio);
	green = color_lvl((start_col >> 8) & 0xFF, (end_col >> 8) & 0xFF, ratio);
	blue = color_lvl(start_col & 0xFF, end_col & 0xFF, ratio);
	return ((red << 16) | (green << 8) | blue);
}

static int	y_gradient(t_point p, t_point p1, t_point p2)
{
	double	ratio;
	int		red;
	int		green;
	int		blue;

	ratio = percent(p.y, p1.y, p2.y);
	red = color_lvl((p1.color >> 16) & 0xFF, (p2.color >> 16) & 0xFF, ratio);
	green = color_lvl((p1.color >> 8) & 0xFF, (p2.color >> 8) & 0xFF, ratio);
	blue = color_lvl(p1.color & 0xFF, p2.color & 0xFF, ratio);
	return ((red << 16) | (green << 8) | blue);
}

int			altitude_color(t_fdf *fdf, double z)
{
	if (fdf->zmax == fdf->zmin)
		return ((z >= 0) ? LOW : SEA);
	else if (z > fdf->zmax / 2)
		return (z_gradient(percent(z, fdf->zmax / 2,
						fdf->zmax), MEDIUM, HIGH));
	else if (z >= 0)
		return (z_gradient(percent(z, 0, fdf->zmax / 2),
					LOW, MEDIUM));
	else
		return (z_gradient(percent(z, fdf->zmin, 0), SEA, SHORE));
}

int			rainbow_color(t_fdf *fdf, t_point p)
{
	t_point	p_max;
	t_point p_min;
	t_point p_moy;

	p_max.y = fdf->ymax * fdf->scale + fdf->y_offset;
	p_max.x = 0;
	p_max.color = 0xFF0000;
	p_min.y = fdf->ymin * fdf->scale + fdf->y_offset;
	p_min.x = 0;
	p_min.color = 0x0000FF;
	p_moy.y = (p_max.y + p_min.y) / 2;
	p_moy.x = 0;
	p_moy.color = 0x00FF00;
	if (p.y >= p_moy.y)
		return (y_gradient(p, p_moy, p_max));
	else
		return (y_gradient(p, p_min, p_moy));
}

int			apply_color(t_fdf *fdf, t_ipos p1, t_ipos p2, t_point p)
{
	int		color;

	if (fdf->color_scheme == MAP)
		color = gradient(fdf, p, fdf->proj[p1.i][p1.j],
				fdf->proj[p2.i][p2.j]);
	else if (fdf->color_scheme == ALTITUDE)
		color = altitude_color(fdf, fdf->map[p1.i][p1.j]
				+ percent(p.y, fdf->proj[p1.i][p1.j].y * fdf->scale
				+ fdf->y_offset, fdf->proj[p2.i][p2.j].y
				* fdf->scale + fdf->y_offset)
				* (fdf->map[p2.i][p2.j] - fdf->map[p1.i][p1.j]));
	else if (fdf->color_scheme == RAINBOW)
		color = rainbow_color(fdf, p);
	else if (fdf->color_scheme == FANCY_RAINBOW)
		color = fdf->rainbow;
	else
		color = 0xFFFFFF;
	return (color);
}
