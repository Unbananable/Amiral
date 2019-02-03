/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 12:06:41 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/02/03 19:38:16 by anleclab         ###   ########.fr       */
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
	if (key == NUMPAD_1 || key == NUMPAD_2 || key == NUMPAD_3
			|| key == NUMPAD_4 || key == NUMPAD_6 || key == NUMPAD_7
			|| key == NUMPAD_8 || key == NUMPAD_9 || key == A || key == W
			|| key == S || key == D || key == Q || key == E
			|| key == Z || key == X || key == SPACE || key == PLUS
			|| key == MINUS || key == NUMPAD_PLUS || key == NUMPAD_MINUS
			|| key == UP_ARROW || key == DOWN_ARROW || key == ESC || key == C)
		return (1);
	return (0);
}

static int	is_altrotate_key(int key)
{
	if (key == UP_ARROW || key == DOWN_ARROW || key == NUMPAD_1
			|| key == NUMPAD_2 || key == NUMPAD_3 || key == NUMPAD_4
			|| key == NUMPAD_6 || key == NUMPAD_7 || key == NUMPAD_8
			|| key == NUMPAD_9)
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
		red_cross_closing(fdf);
	ft_bzero(fdf->addr, WIN_WIDTH * WIN_HEIGHT * 4);
	if (key == A || key == W || key == S || key == D || key == Q || key == E
			|| key == Z || key == X)
		event_move(key, &(fdf->map_info));
	else if (key == SPACE)
		event_reset(fdf);
	else if (key == PLUS || key == MINUS || key == NUMPAD_PLUS
			|| key == NUMPAD_MINUS)
		event_zoom(key, &(fdf->map_info));
	else if (is_altrotate_key(key))
	{
		if (key == UP_ARROW || key == DOWN_ARROW)
			event_adjust_alt(key, &(fdf->map_info));
		else
			event_rotate(key, &(fdf->map_info));
		if (!(projection(fdf)))
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
	if (key == P || key == I || key == T || key == L || key == K)
	{
		ft_bzero(fdf->addr, WIN_WIDTH * WIN_HEIGHT * 4);
		if (key == P)
			PROJ = PARALLEL;
		if (key == I)
			PROJ = ISOMETRIC;
		if (key == T)
			PROJ = TOP;
		if (key == L || key == K)
		{
			fdf->map_info.color_scheme = (key == L) ? ALTITUDE : RAINBOW;
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
