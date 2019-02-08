/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 16:29:47 by anleclab          #+#    #+#             */
/*   Updated: 2019/02/08 14:10:59 by anleclab         ###   ########.fr       */
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
			fdf->beta -= ANGLE_INCR;
		else if (key == PAD_8)
			fdf->alpha += ANGLE_INCR;
		else if (key == PAD_6)
			fdf->beta += ANGLE_INCR;
		else if (key == PAD_2)
			fdf->alpha -= ANGLE_INCR;
		else if (key == PAD_7 || key == PAD_9)
			fdf->gamma += ANGLE_INCR;
		else if (key == PAD_1 || key == PAD_3)
			fdf->gamma -= ANGLE_INCR;
	}
	if (key == A || key == Z || key == Q)
		fdf->x_offset -= OFFSET_INCR;
	if (key == D || key == E || key == X)
		fdf->x_offset += OFFSET_INCR;
	if (key == S || key == Z || key == X)
		fdf->y_offset += OFFSET_INCR;
	if (key == W || key == E || key == Q)
		fdf->y_offset -= OFFSET_INCR;
}

void	event_zoom(int key, double *scale)
{
	if (key == PLUS || key == PAD_PLUS || key == MOUSE_SCROLL_UP)
		*scale *= 1 + ZOOM_INCR;
	else if (key == MINUS || key == PAD_MINUS || key == MOUSE_SCROLL_DOWN)
		*scale *= 1 - ZOOM_INCR;
}

void	event_adjust_alt(int key, double *alt_ratio)
{
	if (key == UP_ARROW)
		*alt_ratio *= 1 + ALT_INCR;
	else if (key == DOWN_ARROW)
		*alt_ratio *= 1 - ALT_INCR;
}

void	event_reset(t_fdf *fdf)
{
	fdf->color_scheme = MAP;
	fdf->alt_ratio = 1;
	fdf->alpha = 0;
	fdf->beta = 0;
	fdf->gamma = 0;
	if (!projection(fdf))
		error("error: failed to reset map", fdf);
	get_placement_info(fdf);
}

void	event_rainbow(t_fdf *fdf)
{
	if (fdf->rainbow & 0xFF0000
			&& !(fdf->rainbow & 0x0000FF))
	{
		fdf->rainbow -= 0x0f0000;
		fdf->rainbow += 0x000f00;
	}
	else if (fdf->rainbow & 0x00FF00
			&& !(fdf->rainbow & 0xFF0000))
	{
		fdf->rainbow -= 0x000f00;
		fdf->rainbow += 0x00000f;
	}
	else if (fdf->rainbow & 0x0000FF
			&& !(fdf->rainbow & 0x00FF00))
	{
		fdf->rainbow -= 0x00000f;
		fdf->rainbow += 0x0f0000;
	}
}
