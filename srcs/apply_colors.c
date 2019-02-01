/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:13:13 by anleclab          #+#    #+#             */
/*   Updated: 2019/02/01 18:17:31 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static double	percent(double current, double start, double end)
{
	return ((current - start) / (end - start));
}

static int		color_lvl(int start, int end, double ratio)
{
	return ((int)((1 - ratio) * start + ratio * end));
}

static int		p_gradient(t_point p, t_point p1, t_point p2)
{
	double	ratio;
	int		red;
	int		green;
	int		blue;

	ratio = (p2.x - p1.x > p2.y - p1.y) ? percent(p.x, p1.x, p2.x)
			: percent(p.y, p1.y, p2.y);
	red = 0;
	green = color_lvl((p1.color >> 8) & 0xFF, (p2.color >> 8) & 0xFF, ratio);
	blue = 0;
	if (!((p2.color >> 16) & 0xFF))
		blue = 255 - green;
	else if (!(p1.color & 0xFF))
		red = 255 - green;
	return ((red << 16) | (green << 8) | blue);
}

static void	altitude_colors(t_fdf *fdf)
{
	fdf += 0;
	return ;
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
					= p_gradient(fdf->proj_map[i][j], p_moy, p_max);
			else
				fdf->proj_map[i][j].color
					= p_gradient(fdf->proj_map[i][j], p_min, p_moy);
		}
}

void		apply_colors(t_fdf *fdf)
{
	if (fdf->map_info.color_scheme == MONO)
		;
	else if (fdf->map_info.color_scheme == MAP)
		;
	else if (fdf->map_info.color_scheme == ALTITUDE)
		altitude_colors(fdf);
	else if (fdf->map_info.color_scheme == RAINBOW)
		rainbow_color(fdf);
}
