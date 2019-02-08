/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 16:29:32 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/02/08 13:49:41 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "fdf.h"
#include "keys.h"

int		mouse_press(int button, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	if (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN)
	{
		ft_bzero(fdf->addr, WIN_WIDTH * WIN_HEIGHT * 4);
		event_zoom(button, &(fdf->scale));
		draw_image(fdf);
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
	}
	else if (button == MOUSE_LEFT_CLICK)
		fdf->mouse.pressed = 1;
	return (0);
}

int		mouse_release(int button, int x, int y, t_fdf *fdf)
{
	(void)button;
	(void)x;
	(void)y;
	fdf->mouse.pressed = 0;
	return (0);
}

int		mouse_move(int x, int y, t_fdf *fdf)
{
	fdf->mouse.last_x = fdf->mouse.x;
	fdf->mouse.last_y = fdf->mouse.y;
	fdf->mouse.x = x;
	fdf->mouse.y = y;
	if (fdf->mouse.pressed == 1)
	{
		ft_bzero(fdf->addr, WIN_WIDTH * WIN_HEIGHT * 4);
		fdf->beta += (x - fdf->mouse.last_x) * MOUSE_ROTATION_COEF;
		fdf->alpha += (y - fdf->mouse.last_y) * MOUSE_ROTATION_COEF;
		get_placement_info(fdf);
		projection(fdf);
		draw_image(fdf);
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
	}
	return (0);
}
