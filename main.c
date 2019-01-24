/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 17:51:55 by anleclab          #+#    #+#             */
/*   Updated: 2019/01/24 18:40:08 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mlx.h"
#include "fdf.h"
#include "libft/includes/libft.h"
#include "libft/includes/ft_printf.h"
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>

static void	init_map_info(t_map *map_info, char *file_name)
{
	int		fd;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		error("FILE PAS BON");
	map_info->width = 0;
	map_info->depth = ft_filelinecount(fd);
	map_info->xmax = 0;
	map_info->xmin = 0;
	map_info->ymax = 0;
	map_info->ymin = 0;
	map_info->scale = 1;
	map_info->x_offset = 0;
	map_info->y_offset = 0;
	map_info->zmax = 0;
	map_info->zmin = 0;
	close(fd);
}

int		red_cross_closing(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

int		mouse_press(int button, int x, int y, void *param)
{
	ft_printf("Mouse press: %d (x,y): %d,%d\n", button, x, y);
	return (0);
}

int		mouse_release(int button, int x, int y, void *param)
{
	ft_printf("Mouse release: %d (x,y): %d,%d\n", button, x, y);
	return (0);
}

int		key_press(int key, void *param)
{
	ft_printf("Key press: %d\n", key);
	if (key == 53)
		exit(1);
	return (0);
}

int		key_release(int key, t_fdf *fdf)
{
	ft_printf("Key release: %d\n", key);
	if (key == 34 || key == 35 || key == 17)
	{
		fdf->img_ptr = mlx_new_image(fdf->mlx_ptr, fdf->map_info.width, fdf->map_info.depth);
		if (key == 35) //'P'
			fdf->proj_map = parallel_projection(fdf->map, &fdf->map_info);
		if (key == 34) //'I'
			fdf->proj_map = isometric_projection(fdf->map, &fdf->map_info);
		if (key == 17)
			fdf->proj_map = top_projection(fdf->map, &fdf->map_info);
		get_placement_info(fdf->proj_map, &fdf->map_info);
		draw(*fdf, fdf->proj_map, fdf->map_info);
		mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
		mlx_destroy_image(fdf->mlx_ptr, fdf->img_ptr);
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

void	usage(void)
{
	ft_putstr("usage: ./fdf map_filename\n");
	exit(0);
}

int		main(int ac, char **av)
{
	t_fdf	*fdf;

	if (ac != 2)
		usage();
	if (!(fdf = (t_fdf *)malloc(sizeof(t_fdf) * 1000)))
		exit(1);
	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIN_HEIGHT, WIN_WIDTH, "FdF");
	init_map_info(&fdf->map_info, av[1]);
	fdf->map = reader(av[1], &fdf->map_info);
	fdf->proj_map = parallel_projection(fdf->map, &fdf->map_info);
	get_placement_info(fdf->proj_map, &fdf->map_info);
	draw(*fdf, fdf->proj_map, fdf->map_info);
	mlx_hook(fdf->win_ptr, 2, 0, key_press, (void *)0);
	mlx_hook(fdf->win_ptr, 3, 0, key_release, fdf);
//	mlx_mouse_hook(win.win_ptr, mouse_hook, (void *)0);
/* On veut tracer une ligne avec les deux prochaines instructions             */
	mlx_hook(fdf->win_ptr, 4, 0, mouse_press, (void *)0);
	mlx_hook(fdf->win_ptr, 5, 0, mouse_release, (void *)0);
/* ************************************************************************** */
	mlx_hook(fdf->win_ptr, 17, 0, red_cross_closing, (void *)0);
	mlx_loop(fdf->mlx_ptr);
	return (0);
}
