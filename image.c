/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 14:05:36 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/01/27 15:00:24 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include <math.h>
#include <stdlib.h>
#include "libft/includes/libft.h"

#include <stdio.h>

/*t_image	*del_image(t_fdf *fdf, t_image *image)
  {
  if (image)
  {
  if (fdf->img_ptr)
  mlx_destroy_image(fdf->mlx_ptr, fdf->img_ptr);
  ft_memdel((void **)&image);
  }
  return (NULL);
  }*/

void	clear_image(t_fdf *fdf)
{
	ft_bzero(fdf->addr, WIN_WIDTH * WIN_HEIGHT * 4);
}

void	fill_pixel(t_fdf *fdf, t_point p)
{
	int		x;
	int		y;

	x = p.x + fdf->map_info.x_offset;
	y = p.y + fdf->map_info.y_offset;
	if (x >= 0 && y >= 0 && x < WIN_WIDTH && y < WIN_HEIGHT)
	{//on pourra mettre une couleur variable apres
		fdf->addr[x + y * WIN_WIDTH] = 0xFF0000;
	}
}
void	new_image(t_fdf *fdf)
{
	fdf->img_ptr = mlx_new_image(fdf->mlx_ptr, WIN_WIDTH , WIN_HEIGHT);
	fdf->addr = (unsigned int *)mlx_get_data_addr(fdf->img_ptr, &(fdf->image.bpp), &(fdf->image.size_line), &(fdf->image.endian));
}

static void	low_line(t_fdf *fdf, t_point p0, t_point p1, t_map map_info)
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

void		draw_line(t_fdf *fdf, t_point p0, t_point p1, t_map map_info)
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

void	draw_img(t_fdf *fdf, t_point **points, t_map map_info)
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
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
}
