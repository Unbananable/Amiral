/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 14:04:47 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/01/24 16:53:44 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include "libft/includes/libft.h"
#include <math.h>

static void	low_line(t_fdf fdf, t_point p0, t_point p1, t_map map_info)
{
	t_point p;
	int	dx;
	int	dy;
	int	yi;
	int	delta;

	dx = (p1.x - p0.x) * map_info.scale;
	dy = (p1.y - p0.y) * map_info.scale;
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	delta = 2 * dy - dx;
	p.y = p0.y * map_info.scale + map_info.y_offset;
	p.x = p0.x * map_info.scale + map_info.x_offset;
	while (p.x <= p1.x * map_info.scale + map_info.x_offset)
	{
		mlx_pixel_put(fdf.mlx_ptr, fdf.win_ptr, p.x, WIN_HEIGHT - p.y, 0xffdd75); //jaune
		if (delta > 0)
		{
			p.y = p.y + yi;
			delta -= 2 * dx;
		}
		delta += 2 * dy;
		p.x++;
	}
}

static void	high_line(t_fdf fdf, t_point p0, t_point p1, t_map map_info)
{
	t_point p;
	int	dx;
	int	dy;
	int	xi;
	int	delta;

	dx = (p1.x - p0.x) * map_info.scale;
	dy = (p1.y - p0.y) * map_info.scale;
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	delta = 2 * dx - dy;
	p.y = p0.y * map_info.scale + map_info.y_offset;
	p.x = p0.x * map_info.scale + map_info.x_offset;
	while (p.y <= p1.y * map_info.scale + map_info.y_offset)
	{
		mlx_pixel_put(fdf.mlx_ptr, fdf.win_ptr, p.x, WIN_HEIGHT - p.y, 0xffdd75); //jaune
		if (delta > 0)
		{
			p.x = p.x + xi;
			delta -= 2 * dy;
		}
		delta += 2 * dx;
		p.y++;
	}
}

void		draw_line(t_fdf fdf, t_point p0, t_point p1, t_map map_info)
{
	if (fabs(p1.y - p0.y) < fabs(p1.x - p0.x))
		if (p0.x > p1.x)
			low_line(fdf, p1, p0, map_info);
		else
			low_line(fdf, p0, p1, map_info);
	else
		if (p0.y > p1.y)
			high_line(fdf, p1, p0, map_info);
		else
			high_line(fdf, p0, p1, map_info);
}

void	draw(t_fdf fdf, t_point **points, t_map map_info)
{
	int		i;
	int		j;

	i = 0;
	while (i < map_info.depth)
	{
		j = 0;
		while (j < map_info.width)
		{
			if (i != map_info.depth - 1)
				draw_line(fdf, points[i][j], points[i + 1][j], map_info);
			if (j != map_info.width - 1)
				draw_line(fdf, points[i][j], points[i][j + 1], map_info);
			j++;
		}
		i++;
	}
}
