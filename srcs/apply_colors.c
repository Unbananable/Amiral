/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:13:13 by anleclab          #+#    #+#             */
/*   Updated: 2019/02/01 16:46:18 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

	p_max.y = (YMAX - Y_OFFSET) / SCALE;
	p_max.x = 0;
	p_max.color = 0xFF0000;
	p_min.y = (YMIN - Y_OFFSET) / SCALE;
	p_min.x = 0;
	p_min.color = 0x0000FF;
	p_moy.y = (p_max.y - p_min.y) / 2;
	p_moy.x = 0;
	p_moy.color = 0x00FF00;
	i = -1;
	while (++i < DEPTH && (j = -1))
		while (++j < WIDTH)
		{
			if (fdf->proj_map[i][j].y >= p_moy.y * SCALE + Y_OFFSET)
				fdf->proj_map[i][j].color
					= gradient(fdf, fdf->proj_map[i][j], p_moy, p_max);
			else
				fdf->proj_map[i][j].color
					= gradient(fdf, fdf->proj_map[i][j], p_min, p_moy);
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
