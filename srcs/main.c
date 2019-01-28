/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 17:51:55 by anleclab          #+#    #+#             */
/*   Updated: 2019/01/28 18:39:03 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mlx.h"
#include "fdf.h"
#include "libft.h"

static int	get_width(char *file_name)
{
	int		res;
	t_file	*stream;
	int		tmp;

	if (!(stream = ft_fopen(file_name)))
		error("BAD FILE");
	res = 0;
	tmp = ft_fgetc(stream);
	while (tmp != -1 && tmp != '\n')
	{
		while (tmp == ' ' || tmp == '\t')
			tmp = ft_fgetc(stream);
		if (tmp == '-' || (tmp >= '0' && tmp <= '9'))
			res++;
		while (tmp == '-' || (tmp >= '0' && tmp <= '9'))
			tmp = ft_fgetc(stream);
		if (tmp != '-' && tmp != ' ' && tmp != '\t' && (tmp < '0'
					|| tmp > '9') && tmp != -1 && tmp != '\n')
		{
			ft_fclose(stream);
			error("INVALID CHARACTER");
		}
	}
	ft_fclose(stream);
	return (res);	
}

static void	init_map_info(t_map *map_info, char *file_name)
{
	if ((DEPTH = ft_filelinecount(file_name)) == -1)
		error("FILE PAS BON");
	if ((WIDTH = get_width(file_name)) == -1)
		error("FILE PAS BON");
	map_info->alt_ratio = 1;
}

static void	usage(void)
{
	ft_putstr("usage: ./fdf map_filename\n");
	exit(0);
}

int			main(int ac, char **av)
{
	t_fdf	fdf;

	if (ac != 2)
		usage();
	fdf.mlx_ptr = mlx_init();
	fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, WIN_HEIGHT, WIN_WIDTH, "FdF");
	init_map_info(&(fdf.map_info), av[1]);
	fdf.map = reader(av[1], &(fdf.map_info));
	fdf.proj_map = projection(PARALLEL, fdf.map, &(fdf.map_info));
	get_placement_info(&(fdf.map_info));
	new_image(&fdf);
	mlx_put_image_to_window(fdf.mlx_ptr, fdf.win_ptr, fdf.img_ptr, 0, 0);
	draw_image(&fdf);
	mlx_hook(fdf.win_ptr, 2, 0, &key_press, &fdf);
	mlx_hook(fdf.win_ptr, 3, 0, &key_release, &fdf);
	mlx_hook(fdf.win_ptr, 17, 0, &red_cross_closing, (void *)0);
	mlx_loop(fdf.mlx_ptr);
	return (0);
}
