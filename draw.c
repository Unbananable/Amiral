/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 14:04:47 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/01/18 17:15:11 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include "libft/includes/libft.h"

static void	low_line(t_win win, t_point p0, t_point p1, t_map map_info)
{
	t_point p;
	int	dx;
	int	dy;
	int	yi;
	int	delta;

	dx = p1.x - p0.x;
	dy = p1.y - p0.y;
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	delta = 2 * dy - dx;
	p.y = p0.y;
	p.x = p0.x;
	while (p.x <= p1.x)
	{
		mlx_pixel_put(win.mlx_ptr, win.win_ptr, p.x * map_info.scale, p.y * map_info.scale, 0xffdd75); //jaune
		if (delta > 0)
		{
			p.y = p.y + yi;
			delta -= 2 * dx;
		}
		delta += 2 * dy;
		p.x++;
	}
}

static void	high_line(t_win win, t_point p0, t_point p1, t_map map_info)
{
	t_point p;
	int	dx;
	int	dy;
	int	xi;
	int	delta;

	dx = p1.x - p0.x;
	dy = p1.y - p0.y;
	xi = 1;
	if (dy < 0)
	{
		xi = -1;
		dx = -dx;
	}
	delta = 2 * dx - dy;
	p.y = p0.y;
	p.x = p0.x;
	while (p.y <= p1.y)
	{
		mlx_pixel_put(win.mlx_ptr, win.win_ptr, p.x * map_info.scale, p.y * map_info.scale, 0xffdd75); //jaune
		if (delta > 0)
		{
			p.x = p.x + xi;
			delta -= 2 * dy;
		}
		delta += 2 * dx;
		p.y++;
	}
}

void		draw_line(t_win win, t_point p0, t_point p1, t_map map_info)
{
	if (ft_abs(p1.y - p0.y) < ft_abs(p1.x - p0.x))
		if (p0.x > p1.x)
			low_line(win, p1, p0, map_info);
		else
			low_line(win, p0, p1, map_info);
	else
		if (p0.y > p1.y)
			high_line(win, p1, p0, map_info);
		else
			high_line(win, p0, p1, map_info);
}

void	draw_in_win(t_win win, t_point **points, t_map map_info)
{
	int		i;
	int		j;

	i = 0;
	map_info.scale = 10;
	while (i < map_info.depth)
	{
		j = 0;
		while (j < map_info.width)
		{
			if (i != map_info.depth - 1 && points[i + 1][j].x && points[i + 1][j].y)
				draw_line(win, points[i][j], points[i + 1][j], map_info);
			if (j != map_info.width - 1 && points[i][j + 1].x && points[i][j + 1].y)
				draw_line(win, points[i][j], points[i][j + 1], map_info);
			j++;
		}
		i++;
	}
}
