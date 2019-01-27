/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 12:06:41 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/01/27 17:42:42 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include <stdlib.h>

#include "libft/includes/ft_printf.h"

int		red_cross_closing(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

int		mouse_press(int button, int x, int y, t_fdf *fdf)
{
	ft_printf("Mouse press: %d (x,y): %d,%d\n", button, x, y);
	return (0);
}

int		mouse_release(int button, int x, int y, t_fdf *fdf)
{
	ft_printf("Mouse release: %d (x,y): %d,%d\n", button, x, y);
	return (0);
}

int		key_press(int key, t_fdf *fdf)
{
	ft_printf("Key press: %d\n", key);
	if (key == ESC)
		exit(0);
	if ((key >= LEFT_ARROW && key <= UP_ARROW) || key == SPACE)
	{
		clear_image(fdf);
		if (key == LEFT_ARROW)
			fdf->map_info.x_offset--;
		else if (key == RIGHT_ARROW)
			fdf->map_info.x_offset++;
		else if (key == DOWN_ARROW)
			fdf->map_info.y_offset++;
		else if (key == UP_ARROW)
			fdf->map_info.y_offset--;
		else if (key == SPACE)
			get_placement_info(fdf->proj_map, &(fdf->map_info));
		draw_img(fdf, fdf->proj_map, fdf->map_info);
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
	}
	if (key == PLUS || key == MINUS || key == NUMPAD_PLUS || key == NUMPAD_MINUS)
	{
		clear_image(fdf);
		if (key == PLUS || key == NUMPAD_PLUS)
			fdf->map_info.scale *= 1.01;
		if (key == MINUS || key == NUMPAD_MINUS)
			fdf->map_info.scale *= 0.99;;
		draw_img(fdf, fdf->proj_map, fdf->map_info);
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
	}
	return (0);
}

#include <stdio.h>

int		key_release(int key, t_fdf *fdf)
{
	ft_printf("Key release: %d\n", key);
	if (key == P || key == I || key == T)
	{
		clear_image(fdf);
		if (key == P) //'P'
			fdf->proj_map = parallel_projection(fdf->map, &(fdf->map_info));
		if (key == I) //'I'
			fdf->proj_map = isometric_projection(fdf->map, &(fdf->map_info));
		if (key == T)
			fdf->proj_map = top_projection(fdf->map, &(fdf->map_info));
		get_placement_info(fdf->proj_map, &(fdf->map_info));
		draw_img(fdf, fdf->proj_map, fdf->map_info);
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
	}
	return (0);
}

/* ******************* BONUS IDEAS ****************************************** */
/*	if (key >= 123 || key <= 126)
		camera_arrow(key,...); //camera_top, camera_bot, camera_right, camera_left
	if (key == 4 || key == 5 || key == 24 || key == 27 || key == 69 || key == 78)
		camera_lense(key,...); //camera_zoom, camera_unzoom (+: 69 24 4) (-: 78 27 5)
	if (key == ? -Make a choice-)
		color_panel(key,...); //Several sets of colors, depending of the key ('1'(key 18) to '5'(key 23) for example)
	if (key == 35 ('P'))
		switch_projection(); //Switch between the 2 projections (+ affichage graphique du nom de la projection ?)
	if (key == 8 ('C'))
		activation_colours(); //Activation/désactivation des couleurs (une touche pour activer les couleurs et une touche pour les desactiver ou sinon il faut un interrupteur (var static ?) pour mémoriser si les couleurs sont actuellement affichées ou non)*/
/* ************************************************************************** */
