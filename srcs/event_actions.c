/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 16:29:47 by anleclab          #+#    #+#             */
/*   Updated: 2019/02/03 19:36:57 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "keys.h"

void	event_rotate(int key, t_map *map_info)
{
	if (key == NUMPAD_4)
		map_info->beta -= 0.1;
	else if (key == NUMPAD_2)
		map_info->alpha += 0.1;
	else if (key == NUMPAD_6)
		map_info->beta += 0.1;
	else if (key == NUMPAD_8)
		map_info->alpha -= 0.1;
	else if (key == NUMPAD_3 || key == NUMPAD_1)
		map_info->gamma += 0.1;
	else if (key == NUMPAD_7 || key == NUMPAD_9)
		map_info->gamma -= 0.1;
}

void	event_move(int key, t_map *map_info)
{
	if (key == A || key == Z || key == Q)
		map_info->x_offset -= DIR_INCR;
	if (key == D || key == E || key == X)
		map_info->x_offset += DIR_INCR;
	if (key == S || key == Z || key == X)
		map_info->y_offset += DIR_INCR;
	if (key == W || key == E || key == Q)
		map_info->y_offset -= DIR_INCR;
}

void	event_zoom(int key, t_map *map_info)
{
	if (key == PLUS || key == NUMPAD_PLUS)
		map_info->scale *= 1.02;
	else if (key == MINUS || key == NUMPAD_MINUS)
		map_info->scale *= 0.98;
}

void	event_adjust_alt(int key, t_map *map_info)
{
	if (key == UP_ARROW)
		map_info->alt_ratio *= 1.1;
	else if (key == DOWN_ARROW)
		map_info->alt_ratio *= 0.9;
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
				fdf->proj_map[i][j].color -= 0x050000;
				fdf->proj_map[i][j].color += 0x000500;
			}
			else if (fdf->proj_map[i][j].color & 0x00FF00
					&& !(fdf->proj_map[i][j].color & 0xFF0000))
			{
				fdf->proj_map[i][j].color -= 0x000500;
				fdf->proj_map[i][j].color += 0x000005;
			}
			else if (fdf->proj_map[i][j].color & 0x0000FF
					&& !(fdf->proj_map[i][j].color & 0x00FF00))
			{
				fdf->proj_map[i][j].color -= 0x000005;
				fdf->proj_map[i][j].color += 0x050000;
			}
		}
	}
}
