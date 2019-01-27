/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 12:06:41 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/01/27 17:52:58 by dtrigalo         ###   ########.fr       */
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
	static int	i = 0;
	static int	j = 0;

	ft_printf("Key press: %d\n", key);
	if (key == 53)
		exit(0);
	if (key == 13 || key == 0 || key == 1 || key == 2)
// peut etre macro KEY_W, KEY_A,... pour eviter les magic nbrs ?
	{
		mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
		if (key == 0) // gauche
			mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, --i, j);
		else if (key == 2)// droite
			mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, ++i, j);
		else if (key == 1)// bas
			mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, i, ++j);
		else if (key == 13)// haut
			mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, i, --j);
	}
	if (key == 49)
	{
		i = 0;
		j = 0;
		mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
	}
	if (key == 126 || key == 125) //ARROW_UP, ARROW_DOWN
	{
		mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
		clear_image(fdf);
		if (key == 126)
			fdf->map_info.alt_ratio *= 1.1;
		else if (key == 125)
			fdf->map_info.alt_ratio *= 0.9;
		if (fdf->map_info.proj == ISOMETRIC)
			fdf->proj_map = isometric_projection(fdf->map, &(fdf->map_info));
		else if (fdf->map_info.proj == PARALLEL)
			fdf->proj_map = parallel_projection(fdf->map, &(fdf->map_info));
		draw_img(fdf, fdf->proj_map, fdf->map_info);
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
	}
	return (0);
}

#include <stdio.h>

int		key_release(int key, t_fdf *fdf)
{
	ft_printf("Key release: %d\n", key);
	if (key == 34 || key == 35 || key == 17)
	{
		clear_image(fdf);
		if (key == 35) //'P'
			fdf->proj_map = parallel_projection(fdf->map, &(fdf->map_info));
		if (key == 34) //'I'
			fdf->proj_map = isometric_projection(fdf->map, &(fdf->map_info));
		if (key == 17)
			fdf->proj_map = top_projection(fdf->map, &(fdf->map_info));
		get_placement_info(fdf->proj_map, &(fdf->map_info));
		printf("xmax: %f... xmin: %f... ymax: %f... ymin: :%f\n", fdf->map_info.xmax, fdf->map_info.xmin, fdf->map_info.ymax, fdf->map_info.ymin);
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
