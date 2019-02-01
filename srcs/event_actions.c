/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 16:29:47 by anleclab          #+#    #+#             */
/*   Updated: 2019/02/01 14:12:40 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "keys.h"

void	event_move(int key, t_map *map_info)
{
	if (key == A || key == Z || key == Q)
		map_info->x_offset -= 3;
	if (key == D || key == E || key == X)
		map_info->x_offset += 3;
	if (key == S || key == Z || key == X)
		map_info->y_offset += 3;
	if (key == W || key == E || key == Q)
		map_info->y_offset -= 3;
}

void	event_zoom(int key, t_map *map_info)
{
	if (key == PLUS || key == NUMPAD_PLUS)
		map_info->scale *= 1.02;
	if (key == MINUS || key == NUMPAD_MINUS)
		map_info->scale *= 0.98;
}

void	event_adjust_alt(int key, t_map *map_info)
{
	if (key == UP_ARROW)
		map_info->alt_ratio *= 1.1;
	if (key == DOWN_ARROW)
		map_info->alt_ratio *= 0.9;
}

void	event_reset(t_fdf *fdf)
{
	fdf->map_info.alt_ratio = 1;
	if (!projection(fdf))
		error("error: failed to reset map", fdf);
	get_placement_info(fdf);
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
			if (fdf->proj_map[i][j].colour & 0xFF0000
					&& fdf->proj_map[i][j].colour & 0x00FF00
					&& fdf->proj_map[i][j].colour & 0x0000FF)
				fdf->proj_map[i][j].colour = 0xFF0000;
			else if (fdf->proj_map[i][j].colour & 0xFF0000
					&& !(fdf->proj_map[i][j].colour & 0x0000FF))
			{
				fdf->proj_map[i][j].colour -= 0x050000;
				fdf->proj_map[i][j].colour += 0x000500;
			}
			else if (fdf->proj_map[i][j].colour & 0x00FF00
					&& !(fdf->proj_map[i][j].colour & 0xFF0000))
			{
				fdf->proj_map[i][j].colour -= 0x000500;
				fdf->proj_map[i][j].colour += 0x000005;
			}
			else if (fdf->proj_map[i][j].colour & 0x0000FF
					&& !(fdf->proj_map[i][j].colour & 0x00FF00))
			{
				fdf->proj_map[i][j].colour -= 0x000005;
				fdf->proj_map[i][j].colour += 0x050000;
			}
		}
	}
}
