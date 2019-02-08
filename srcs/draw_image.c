/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 14:05:36 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/02/08 12:53:55 by anleclab         ###   ########.fr       */
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

static void	low_line(t_fdf *fdf, t_ipos p1, t_ipos p2)
{
	t_point p;
	int		dx;
	int		dy;
	int		yi;
	int		delta;

	dx = (fdf->proj[p2.i][p2.j].x - fdf->proj[p1.i][p1.j].x) * fdf->scale;
	dy = (fdf->proj[p2.i][p2.j].y - fdf->proj[p1.i][p1.j].y) * fdf->scale;
	yi = (dy < 0) ? -1 : 1;
	dy = (dy < 0) ? -dy : dy;
	delta = 2 * dy - dx;
	p.y = fdf->proj[p1.i][p1.j].y * fdf->scale + fdf->y_offset;
	p.x = fdf->proj[p1.i][p1.j].x * fdf->scale + fdf->x_offset;
	while (p.x <= fdf->proj[p2.i][p2.j].x * fdf->scale + fdf->x_offset)
	{
		if (fdf->color_scheme == MONO)
			p.color = 0xFFFFFF;
		else if (fdf->color_scheme == MAP)
			p.color = gradient(fdf, p, fdf->proj[p1.i][p1.j], fdf->proj[p2.i][p2.j]);
		else if (fdf->color_scheme == ALTITUDE)
			p.color = altitude_color(fdf, fdf->map[p1.i][p1.j]
						+ percent(p.x, fdf->proj[p1.i][p1.j].x * fdf->scale
						+ fdf->x_offset, fdf->proj[p2.i][p2.j].x * fdf->scale
						+ fdf->x_offset)
						* (fdf->map[p2.i][p2.j] - fdf->map[p1.i][p1.j]));
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

static void	high_line(t_fdf *fdf, t_ipos p1, t_ipos p2)
{
	t_point p;
	int		dx;
	int		dy;
	int		xi;
	int		delta;

	dx = (fdf->proj[p1.i][p2.i].x - fdf->proj[p1.i][p1.j].x) * fdf->scale;
	dy = (fdf->proj[p2.i][p2.j].y - fdf->proj[p1.i][p1.j].y) * fdf->scale;
	xi = (dx < 0) ? -1 : 1;
	dx = (dx < 0) ? -dx : dx;
	delta = 2 * dx - dy;
	p.y = fdf->proj[p1.i][p1.j].y * fdf->scale + fdf->y_offset;
	p.x = fdf->proj[p1.i][p1.j].x * fdf->scale + fdf->x_offset;
	while (p.y <= fdf->proj[p2.i][p2.j].y * fdf->scale + fdf->y_offset)
	{
		if (fdf->color_scheme == MONO)
			p.color = 0xFFFFFF;
		else if (fdf->color_scheme == MAP)
			p.color = gradient(fdf, p, fdf->proj[p1.i][p1.j], fdf->proj[p2.i][p2.j]);
		else if (fdf->color_scheme == ALTITUDE)
			p.color = altitude_color(fdf, fdf->map[p1.i][p1.j]
					+ percent(p.y, fdf->proj[p1.i][p1.j].y * fdf->scale
					+ fdf->y_offset, fdf->proj[p2.i][p2.j].y
					* fdf->scale + fdf->y_offset)
					* (fdf->map[p2.i][p2.j] - fdf->map[p1.i][p1.j]));
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

static void	draw_line(t_fdf *fdf, t_ipos p1, t_ipos p2)
{
	if (fabs(fdf->proj[p2.i][p2.j].y - fdf->proj[p1.i][p1.j].y)
			< fabs(fdf->proj[p2.i][p2.j].x - fdf->proj[p1.i][p1.j].x))
	{
		if (fdf->proj[p1.i][p1.j].x > fdf->proj[p2.i][p2.i].x)
			low_line(fdf, p2, p1);
		else
			low_line(fdf, p1, p2);
	}
	else
	{
		if (fdf->proj[p1.i][p1.j].y > fdf->proj[p2.i][p2.j].y)
			high_line(fdf, p2, p1);
		else
			high_line(fdf, p1, p2);
	}
}

void		draw_image(t_fdf *fdf)
{
	t_ipos	p_beg;
	t_ipos	p_end;
	int		i;
	int		j;
	t_point	p;

	if (fdf->depth == 1 && fdf->width == 1)
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
			{
				p_beg = get_ipos(i, j);
				p_end = get_ipos(i + 1, j);
				draw_line(fdf, p_beg, p_end);
			}
			if (j != fdf->width - 1)
			{
				p_beg = get_ipos(i, j);
				p_end = get_ipos(i, j + 1);
				draw_line(fdf, p_beg, p_end);
			}
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
}
