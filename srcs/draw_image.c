/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 14:05:36 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/02/08 12:19:52 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include <math.h>
#include <stdlib.h>
#include "libft.h"
#include "colors.h"

static void	fill_pixel(t_fdf *fdf, t_point p)
{
	int		x;
	int		y;

	x = p.x;
	y = p.y;
	if (x >= 0 && y >= 0 && x < WIN_WIDTH && y < WIN_HEIGHT)
		fdf->addr[x + y * WIN_WIDTH] = p.color;
}

static void	low_line(t_fdf *fdf, int i1, int j1, int i2, int j2)
{
	t_point p;
	int		dx;
	int		dy;
	int		yi;
	int		delta;

	dx = (fdf->proj[i2][j2].x - fdf->proj[i1][j1].x) * fdf->scale;
	dy = (fdf->proj[i2][j2].y - fdf->proj[i1][j1].y) * fdf->scale;
	yi = (dy < 0) ? -1 : 1;
	dy = (dy < 0) ? -dy : dy;
	delta = 2 * dy - dx;
	p.y = fdf->proj[i1][j1].y * fdf->scale + fdf->y_offset;
	p.x = fdf->proj[i1][j1].x * fdf->scale + fdf->x_offset;
	while (p.x <= fdf->proj[i2][j2].x * fdf->scale + fdf->x_offset)
	{
		if (fdf->color_scheme == MONO)
			p.color = 0xFFFFFF;
		else if (fdf->color_scheme == MAP)
			p.color = gradient(fdf, p, fdf->proj[i1][j1], fdf->proj[i2][j2]);
		else if (fdf->color_scheme == ALTITUDE)
			p.color = altitude_color(fdf, fdf->map[i1][j1]
						+ percent(p.x, fdf->proj[i1][j1].x * fdf->scale
						+ fdf->x_offset, fdf->proj[i2][j2].x * fdf->scale + fdf->x_offset)
						* (fdf->map[i2][j2] - fdf->map[i1][j1]));
		else if (fdf->color_scheme == RAINBOW)
			p.color = rainbow_color(fdf, p);
		else if (fdf->color_scheme == FANCY_RAINBOW)
			p.color = fdf->rainbow;
		fill_pixel(fdf, p);
		if (delta > 0)
		{
			p.y += yi;
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

	dx = (fdf->proj[i2][j2].x - fdf->proj[i1][j1].x) * fdf->scale;
	dy = (fdf->proj[i2][j2].y - fdf->proj[i1][j1].y) * fdf->scale;
	xi = (dx < 0) ? -1 : 1;
	dx = (dx < 0) ? -dx : dx;
	delta = 2 * dx - dy;
	p.y = fdf->proj[i1][j1].y * fdf->scale + fdf->y_offset;
	p.x = fdf->proj[i1][j1].x * fdf->scale + fdf->x_offset;
	while (p.y <= fdf->proj[i2][j2].y * fdf->scale + fdf->y_offset)
	{
		if (fdf->color_scheme == MONO)
			p.color = 0xFFFFFF;
		else if (fdf->color_scheme == MAP)
			p.color = gradient(fdf, p, fdf->proj[i1][j1], fdf->proj[i2][j2]);
		else if (fdf->color_scheme == ALTITUDE)
			p.color = altitude_color(fdf, fdf->map[i1][j1]
					+ percent(p.y, fdf->proj[i1][j1].y * fdf->scale
					+ fdf->y_offset, fdf->proj[i2][j2].y
					* fdf->scale + fdf->y_offset)
					* (fdf->map[i2][j2] - fdf->map[i1][j1]));
		else if (fdf->color_scheme == RAINBOW)
			p.color = rainbow_color(fdf, p);
		else if (fdf->color_scheme == FANCY_RAINBOW)
			p.color = fdf->rainbow;
		fill_pixel(fdf, p);
		if (delta > 0)
		{
			p.x += xi; 
			delta -= 2 * dy;
		}
		delta += 2 * dx;
		p.y++;
	}
}

static void	draw_line(t_fdf *fdf, int i1, int j1, int i2, int j2)
{
	if (fabs(fdf->proj[i2][j2].y - fdf->proj[i1][j1].y)
			< fabs(fdf->proj[i2][j2].x - fdf->proj[i1][j1].x))
	{
		if (fdf->proj[i1][j1].x > fdf->proj[i2][j2].x)
			low_line(fdf, i2, j2, i1, j1);
		else
			low_line(fdf, i1, j1, i2, j2);
	}
	else
	{
		if (fdf->proj[i1][j1].y > fdf->proj[i2][j2].y)
			high_line(fdf, i2, j2, i1, j1);
		else
			high_line(fdf, i1, j1, i2, j2);
	}
}

void		draw_image(t_fdf *fdf)
{
	int		i;
	int		j;
	t_point	p;

	if (DEPTH == 1 && WIDTH == 1)
	{
		p.x = fdf->x_offset;
		p.y = fdf->y_offset;
		if (fdf->color_scheme == MONO)
			p.color = 0xFFFFFF;
		else if (fdf->color_scheme == ALTITUDE)
			p.color = (fdf->map[0][0] < 0) ? SEA : LOW;
		else if (fdf->color_scheme == MAP)
			p.color = fdf->proj[0][0].color;
		else if (fdf->color_scheme == RAINBOW)
			p.color = 0xFF0000;
		else if (fdf->color_scheme == FANCY_RAINBOW)
			p.color = fdf->rainbow;
		fill_pixel(fdf, p);
	}
	i = 0;
	while (i < fdf->depth)
	{
		j = 0;
		while (j < fdf->width)
		{
			if (i != fdf->depth - 1)
				draw_line(fdf, i, j, i + 1, j);
			if (j != fdf->width - 1)
				draw_line(fdf, i, j, i, j + 1);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
}
