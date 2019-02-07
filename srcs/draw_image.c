/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 14:05:36 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/02/07 17:12:29 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include <math.h>
#include <stdlib.h>
#include "libft.h"

static void	fill_pixel(t_fdf *fdf, t_point p, int color)
{
	int		x;
	int		y;

	x = p.x;
	y = p.y;
	if (x >= 0 && y >= 0 && x < WIN_WIDTH && y < WIN_HEIGHT)
		fdf->addr[x + y * WIN_WIDTH] = color;
}

static void	low_line(t_fdf *fdf, int i1, int j1, int i2, int j2)
{
	t_point p;
	int		dx;
	int		dy;
	int		yi;
	int		delta;

	dx = (fdf->proj_map[i2][j2].x - fdf->proj_map[i1][j1].x) * SCALE;
	dy = (fdf->proj_map[i2][j2].y - fdf->proj_map[i1][j1].y) * SCALE;
	yi = (dy < 0) ? -1 : 1;
	dy = (dy < 0) ? -dy : dy;
	delta = 2 * dy - dx;
	p.y = fdf->proj_map[i1][j1].y * SCALE + Y_OFFSET;
	p.x = fdf->proj_map[i1][j1].x * SCALE + X_OFFSET;
	while (p.x <= fdf->proj_map[i2][j2].x * SCALE + X_OFFSET)
	{
		if (fdf->map_info.color_scheme == MONO)
			fill_pixel(fdf, p, fdf->proj_map[i1][j1].color);
		else if (fdf->map_info.color_scheme == ALTITUDE)
			fill_pixel(fdf, p, altitude_color(fdf, fdf->map[i1][j1]
						+ percent(p.x, fdf->proj_map[i1][j1].x * SCALE
						+ X_OFFSET, fdf->proj_map[i2][j2].x * SCALE + X_OFFSET)
						* (fdf->map[i2][j2] - fdf->map[i1][j1])));
		else
			fill_pixel(fdf, p, gradient(fdf, p, fdf->proj_map[i1][j1],
						fdf->proj_map[i2][j2]));
		if (delta > 0)
		{
			p.y = p.y + yi;
			delta -= 2 * dx;
		}
		delta += 2 * dy;
		p.x++;
	}
}

static void	high_line(t_fdf *fdf, int i1, int j1, int i2, int j2)
{
	t_point p;
	int		dx;
	int		dy;
	int		xi;
	int		delta;

	dx = (fdf->proj_map[i2][j2].x - fdf->proj_map[i1][j1].x) * SCALE;
	dy = (fdf->proj_map[i2][j2].y - fdf->proj_map[i1][j1].y) * SCALE;
	xi = (dx < 0) ? -1 : 1;
	dx = (dx < 0) ? -dx : dx;
	delta = 2 * dx - dy;
	p.y = fdf->proj_map[i1][j1].y * SCALE + Y_OFFSET;
	p.x = fdf->proj_map[i1][j1].x * SCALE + X_OFFSET;
	while (p.y <= fdf->proj_map[i2][j2].y * SCALE + Y_OFFSET)
	{
		if (fdf->map_info.color_scheme == MONO)
			fill_pixel(fdf, p, fdf->proj_map[i1][j1].color);
		else if (fdf->map_info.color_scheme == ALTITUDE)
			fill_pixel(fdf, p, altitude_color(fdf, fdf->map[i1][j1]
						+ percent(p.y, fdf->proj_map[i1][j1].y * SCALE
						+ Y_OFFSET, fdf->proj_map[i2][j2].y * SCALE + Y_OFFSET)
						* (fdf->map[i2][j2] - fdf->map[i1][j1])));
		else
			fill_pixel(fdf, p, gradient(fdf, p, fdf->proj_map[i1][j1],
						fdf->proj_map[i2][j2]));
		if (delta > 0)
		{
			p.x = p.x + xi;
			delta -= 2 * dy;
		}
		delta += 2 * dx;
		p.y++;
	}
}

static void	draw_line(t_fdf *fdf, int i1, int j1, int i2, int j2)
{
	if (fabs(fdf->proj_map[i2][j2].y - fdf->proj_map[i1][j1].y)
			< fabs(fdf->proj_map[i2][j2].x - fdf->proj_map[i1][j1].x))
	{
		if (fdf->proj_map[i1][j1].x > fdf->proj_map[i2][j2].x)
			low_line(fdf, i2, j2, i1, j1);
		else
			low_line(fdf, i1, j1, i2, j2);
	}
	else
	{
		if (fdf->proj_map[i1][j1].y > fdf->proj_map[i2][j2].y)
			high_line(fdf, i2, j2, i1, j1);
		else
			high_line(fdf, i1, j1, i2, j2);
	}
}

void		draw_image(t_fdf *fdf)
{
	int		i;
	int		j;

	i = 0;
	while (i < DEPTH)
	{
		j = 0;
		while (j < WIDTH)
		{
			if (i != DEPTH - 1)
				draw_line(fdf, i, j, i + 1, j);
			if (j != WIDTH - 1)
				draw_line(fdf, i, j, i, j + 1);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
}
