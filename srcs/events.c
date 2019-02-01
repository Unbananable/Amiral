/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 12:06:41 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/02/01 14:34:57 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include <stdlib.h>
#include "libft.h"
#include "keys.h"

#include <stdio.h>

static int	is_available(int key)
{
	if (key == A || key == W || key == S || key == D || key == Q || key == E
			|| key == Z || key == X || key == SPACE || key == PLUS
			|| key == MINUS || key == NUMPAD_PLUS || key == NUMPAD_MINUS
			|| key == UP_ARROW || key == DOWN_ARROW || key == ESC || key == C)
		return (1);
	return (0);
}

int			red_cross_closing(t_fdf *fdf)
{
	clear_fdf(fdf);
	exit(0);
	return (0);
}

int			key_press(int key, t_fdf *fdf)
{
	if (!is_available(key))
		return (0);
	if (key == ESC)
	{
		clear_fdf(fdf);
		exit(0);
	}
	ft_bzero(fdf->addr, WIN_WIDTH * WIN_HEIGHT * 4);
	if (key == A || key == W || key == S || key == D || key == Q || key == E
			|| key == Z || key == X)
		event_move(key, &(fdf->map_info));
	else if (key == SPACE)
		event_reset(fdf);
	else if (key == PLUS || key == MINUS || key == NUMPAD_PLUS
			|| key == NUMPAD_MINUS)
		event_zoom(key, &(fdf->map_info));
	else if (key == UP_ARROW || key == DOWN_ARROW)
	{
		event_adjust_alt(key, &(fdf->map_info));
		if(!(projection(fdf)))
			error("error: failed to update projection", fdf);
	}
	else if (key == C)
		event_rainbow(fdf);
	draw_image(fdf);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
	return (0);
}

int			key_release(int key, t_fdf *fdf)
{
printf("key = %d\n", key);
	if (key == P || key == I || key == T || key == L)
	{
		ft_bzero(fdf->addr, WIN_WIDTH * WIN_HEIGHT * 4);
		if (key == P)
			PROJ = PARALLEL;
		if (key == I)
			PROJ = ISOMETRIC;
		if (key == T)
			PROJ = TOP;
		if (key == L)
		{
			fdf->map_info.color_scheme = ALTITUDE;
			apply_colors(fdf);
		}
		else
		{
			if (!projection(fdf))
				error("error: failed to update projection", fdf);
			get_placement_info(fdf);
		}
		draw_image(fdf);
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
	}
	return (0);
}
