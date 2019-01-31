/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 14:05:36 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/01/31 14:39:29 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include <math.h>
#include <stdlib.h>
#include "libft.h"

static void	fill_pixel(t_fdf *fdf, t_point p)
{
	int		x;
	int		y;

	x = p.x;
	y = p.y;
	if (x >= 0 && y >= 0 && x < WIN_WIDTH && y < WIN_HEIGHT)
		fdf->addr[x + y * WIN_WIDTH] = 0xFF0000;
}

static void	low_line(t_fdf *fdf, t_point p0, t_point p1, t_map map_info)
{
	t_point p;
	int		dx;
	int		dy;
	int		yi;
	int		delta;

	dx = (p1.x - p0.x) * map_info.scale;
	dy = (p1.y - p0.y) * map_info.scale;
	yi = (dy < 0) ? -1 : 1;
	dy = (dy < 0) ? -dy : dy;
	delta = 2 * dy - dx;
	p.y = p0.y * map_info.scale + map_info.y_offset;
	p.x = p0.x * map_info.scale + map_info.x_offset;
	while (p.x <= p1.x * map_info.scale + map_info.x_offset)
	{
		fill_pixel(fdf, p);
		if (delta > 0)
		{
			p.y = p.y + yi;
			delta -= 2 * dx;
		}
		delta += 2 * dy;
		p.x++;
	}
}

static void	high_line(t_fdf *fdf, t_point p0, t_point p1, t_map map_info)
{
	t_point p;
	int		dx;
	int		dy;
	int		xi;
	int		delta;

	dx = (p1.x - p0.x) * map_info.scale;
	dy = (p1.y - p0.y) * map_info.scale;
	xi = (dx < 0) ? -1 : 1;
	dx = (dx < 0) ? -dx : dx;
	delta = 2 * dx - dy;
	p.y = p0.y * map_info.scale + map_info.y_offset;
	p.x = p0.x * map_info.scale + map_info.x_offset;
	while (p.y <= p1.y * map_info.scale + map_info.y_offset)
	{
		fill_pixel(fdf, p);
		if (delta > 0)
		{
			p.x = p.x + xi;
			delta -= 2 * dy;
		}
		delta += 2 * dx;
		p.y++;
	}
}

static void	draw_line(t_fdf *fdf, t_point p0, t_point p1, t_map map_info)
{
	if (fabs(p1.y - p0.y) < fabs(p1.x - p0.x))
	{
		if (p0.x > p1.x)
			low_line(fdf, p1, p0, map_info);
		else
			low_line(fdf, p0, p1, map_info);
	}
	else
	{
		if (p0.y > p1.y)
			high_line(fdf, p1, p0, map_info);
		else
			high_line(fdf, p0, p1, map_info);
	}
}

void		draw_image(t_fdf *fdf)
{
	int		i;
	int		j;

	i = 0;
	while (i < fdf->map_info.depth)
	{
		j = 0;
		while (j < fdf->map_info.width)
		{
			if (i != fdf->map_info.depth - 1)
				draw_line(fdf, fdf->proj_map[i][j], fdf->proj_map[i + 1][j],
						fdf->map_info);
			if (j != fdf->map_info.width - 1)
				draw_line(fdf, fdf->proj_map[i][j], fdf->proj_map[i][j + 1],
						fdf->map_info);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
}
