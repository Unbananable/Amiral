/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 17:51:55 by anleclab          #+#    #+#             */
/*   Updated: 2019/01/27 12:19:47 by dtrigalo         ###   ########.fr       */
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
	new_image(fdf);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
	draw_img(fdf, fdf->proj_map, fdf->map_info);
	mlx_hook(fdf->win_ptr, 2, 0, key_press, fdf);
	mlx_hook(fdf->win_ptr, 3, 0, key_release, fdf);
	mlx_hook(fdf->win_ptr, 4, 0, mouse_press, fdf);
	mlx_hook(fdf->win_ptr, 5, 0, mouse_release, (void *)0);
	mlx_hook(fdf->win_ptr, 17, 0, red_cross_closing, (void *)0);
	mlx_loop(fdf->mlx_ptr);
	return (0);
}
