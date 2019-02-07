/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 16:29:47 by anleclab          #+#    #+#             */
/*   Updated: 2019/02/07 14:33:40 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "keys.h"

void	event_move(int key, t_fdf *fdf)
{
	if (key == PAD_1 || key == PAD_2 || key == PAD_3 || key == PAD_4
			|| key == PAD_6 || key == PAD_7 || key == PAD_8 || key == PAD_9)
	{
		if (key == PAD_4)
			fdf->map_info.beta -= ANGLE_INCR;
		else if (key == PAD_8)
			fdf->map_info.alpha += ANGLE_INCR;
		else if (key == PAD_6)
			fdf->map_info.beta += ANGLE_INCR;
		else if (key == PAD_2)
			fdf->map_info.alpha -= ANGLE_INCR;
		else if (key == PAD_7 || key == PAD_9)
			fdf->map_info.gamma += ANGLE_INCR;
		else if (key == PAD_1 || key == PAD_3)
			fdf->map_info.gamma -= ANGLE_INCR;
		get_placement_info(fdf);
	}
	if (key == A || key == Z || key == Q)
		fdf->map_info.x_offset -= OFFSET_INCR;
	if (key == D || key == E || key == X)
		fdf->map_info.x_offset += OFFSET_INCR;
	if (key == S || key == Z || key == X)
		fdf->map_info.y_offset += OFFSET_INCR;
	if (key == W || key == E || key == Q)
		fdf->map_info.y_offset -= OFFSET_INCR;
}

void	event_zoom(int key, t_map *map_info)
{
	if (key == PLUS || key == PAD_PLUS || key == MOUSE_SCROLL_UP)
		map_info->scale *= 1 + ZOOM_INCR;
	else if (key == MINUS || key == PAD_MINUS || key == MOUSE_SCROLL_DOWN)
		map_info->scale *= 1 - ZOOM_INCR;
}

void	event_adjust_alt(int key, t_map *map_info)
{
	if (key == UP_ARROW)
		map_info->alt_ratio *= 1 + ALT_INCR;
	else if (key == DOWN_ARROW)
		map_info->alt_ratio *= 1 - ALT_INCR;
}

void	event_reset(t_fdf *fdf)
{
	fdf->map_info.alt_ratio = 1;
	fdf->map_info.alpha = 0;
	fdf->map_info.beta = 0;
	fdf->map_info.gamma = 0;
	if (!projection(fdf))
		error("error: failed to reset map", fdf);
	get_placement_info(fdf);
}

static int	is_rainbow_color(int color)
{
	if (!(color & 0xFF0000))
		return (((color >> 8) & 0xFF) == 255 - (color & 0xFF));
	if (!(color & 0x00FF00))
		return (((color >> 16) & 0xFF) == 255 - (color & 0xFF));
	if (!(color & 0x0000FF))
		return (((color >> 8) & 0xFF) == 255 - ((color >> 16) & 0xFF));
	return (0);
}

void	event_rainbow(t_fdf *fdf)
{
	int		i;
	int		j;

	i = -1;
	while (++i < DEPTH)
	{
		j = -1;
		while (++j < WIDTH)
		{
			if (!is_rainbow_color(fdf->proj_map[i][j].color))
				fdf->proj_map[i][j].color = 0xFF0000;
			else if (fdf->proj_map[i][j].color & 0xFF0000
					&& !(fdf->proj_map[i][j].color & 0x0000FF))
			{
				fdf->proj_map[i][j].color -= 0x0f0000;
				fdf->proj_map[i][j].color += 0x000f00;
			}
			else if (fdf->proj_map[i][j].color & 0x00FF00
					&& !(fdf->proj_map[i][j].color & 0xFF0000))
			{
				fdf->proj_map[i][j].color -= 0x000f00;
				fdf->proj_map[i][j].color += 0x00000f;
			}
			else if (fdf->proj_map[i][j].color & 0x0000FF
					&& !(fdf->proj_map[i][j].color & 0x00FF00))
			{
				fdf->proj_map[i][j].color -= 0x00000f;
				fdf->proj_map[i][j].color += 0x0f0000;
			}
		}
	}
}
