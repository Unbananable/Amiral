/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 16:29:47 by anleclab          #+#    #+#             */
/*   Updated: 2019/01/29 10:38:06 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "keys.h"

void	event_move(int key, t_map *map_info)
{
	if (key == A || key == Z || key == Q)
		map_info->x_offset--;
	if (key == D || key == E || key == X)
		map_info->x_offset++;
	if (key == S || key == Z || key == X)
		map_info->y_offset++;
	if (key == W || key == E || key == Q)
		map_info->y_offset--;
}

void	event_zoom(int key, t_map *map_info)
{
	if (key == PLUS || key == NUMPAD_PLUS)
		SCALE *= 1.01;
	if (key == MINUS || key == NUMPAD_MINUS)
		SCALE *= 0.99;
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
	free_array_array(&(fdf->proj_map), fdf->map_info.depth);
	if (!(fdf->proj_map = projection(fdf->map_info.proj, fdf->map,
			&(fdf->map_info))))
		error("error: failed to reset map", fdf);
	get_placement_info(&(fdf->map_info));
}
