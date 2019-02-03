/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:13:13 by anleclab          #+#    #+#             */
/*   Updated: 2019/02/03 18:44:56 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "colors.h"

static int	z_gradient(double z, double z1, double z2, int start_col, int end_col)
{
	double	ratio;
	int		red;
	int		green;
	int		blue;

	ratio = percent(z, z1, z2);
	red = color_lvl((start_col >> 16) & 0xFF, (end_col >> 16) & 0xFF, ratio);
	green = color_lvl((start_col >> 8) & 0xFF, (end_col >> 8) & 0xFF, ratio);
	blue = color_lvl(start_col & 0xFF, end_col & 0xFF, ratio);
	return ((red << 16) | (green << 8) | blue);
}

int		altitude_color(t_fdf *fdf, double z)
{
	if (z > ZMAX / 2)
		return(z_gradient(z, ZMAX / 2, ZMAX, MEDIUM, HIGH));
	else if (z >= 0)
		return(z_gradient(z, 0 , ZMAX / 2, LOW, MEDIUM));
	else
		return(z_gradient(z, ZMIN, 0, SEA, SHORE));
}

static void rainbow_color(t_fdf *fdf)
{
	int		i;
	int		j;
	t_point	p_max;
	t_point p_min;
	t_point p_moy;

	p_max.y = YMAX;
	p_max.x = 0;
	p_max.color = 0xFF0000;
	p_min.y = YMIN;
	p_min.x = 0;
	p_min.color = 0x0000FF;
	p_moy.y = (p_min.y - p_max.y) / 2;
	p_moy.x = 0;
	p_moy.color = 0x00FF00;
	i = -1;
	while (++i < DEPTH && (j = -1))
		while (++j < WIDTH)
		{
			if (fdf->proj_map[i][j].y >= p_moy.y)
				fdf->proj_map[i][j].color
					= gradient(fdf, fdf->proj_map[i][j], p_moy, p_max);
			else
				fdf->proj_map[i][j].color
					= gradient(fdf, fdf->proj_map[i][j], p_min, p_moy);
		}
}

void		apply_colors(t_fdf *fdf)
{
	if (fdf->map_info.color_scheme == RAINBOW)
		rainbow_color(fdf);
}
