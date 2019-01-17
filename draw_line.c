/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 14:04:47 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/01/17 17:03:44 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include "libft.h"

static void	low_line(void *mlx_ptr, void * win_ptr, t_point p0, t_point p1)
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
		mlx_pixel_put(mlx_ptr, win_ptr, p.x, p.y, 0xffdd75); //jaune
		if (delta > 0)
		{
			p.y = p.y + yi;
			delta -= 2 * dx;
		}
		delta += 2 * dy;
	}
}

static void	high_line(void *mlx_ptr, void *win_ptr, t_point p0, t_point p1)
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
		mlx_pixel_put(mlx_ptr, win_ptr, p.x, p.y, 0xffdd75); //jaune
		if (delta > 0)
		{
			p.x = p.x + xi;
			delta -= 2 * dy;
		}
		delta += 2 * dx;
	}
}

void		draw_line(void *mlx_ptr, void *win_ptr, t_point p0, t_point p1)
{
	if (ft_abs(p1.y - p0.y) < ft_abs(p1.x - p0.x))
		if (p0.x > p1.x)
			low_line(mlx_ptr, win_ptr, p1, p0);
		else
			low_line(mlx_ptr, win_ptr, p0, p1);
	else
		if (p0.y > p1.y)
			high_line(mlx_ptr, win_ptr, p1, p0);
		else
			high_line(mlx_ptr, win_ptr, p0, p1);
}
