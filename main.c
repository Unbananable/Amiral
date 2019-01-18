/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 17:51:55 by anleclab          #+#    #+#             */
/*   Updated: 2019/01/18 14:38:41 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mlx.h"
#include "fdf.h"
#include "libft/includes/libft.h"

int		deal_key(int key, void *param)
{
//Action qui se déroule à chaque input clavier (on peut par exemple print la
//touche (key) utilisée et s'en servir pour la relier à des actions définies
	key +=0;
	param +=0;
	return (0);
}

void	usage(void)
{
	ft_putstr("usage: ./fdf map_filename\n");
	exit(0);
}

int		main(int ac, char **av)
{

	int		**map;
	t_point **proj_map;
	t_map	map_info;
	t_win	win;

	if (ac != 2)
		usage();
	win.mlx_ptr = mlx_init();
	win.win_ptr = mlx_new_window(win.mlx_ptr, WIN_HEIGHT, WIN_WIDTH, "FdF");
	map = reader(av[1], &map_info);
	proj_map = parallel_projection(map, &map_info);
	draw_in_win(win, proj_map, map_info);
	mlx_loop(win.mlx_ptr);

/*	void	*mlx_ptr;
	void	*win_ptr;
	t_point p0;
	t_point p1;
	ac += 0;
	av += 0;
// TO DO: fonction init_point(x ,y ,z) ?
	p0.x = 1;
	p0.y = 1;
	p1.x = 100;
	p1.y = 100;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1000, 1000, "Bonjour bonjour !!");
	mlx_pixel_put(mlx_ptr, win_ptr, 1000, 1000, 0xFFFFFF);
	mlx_key_hook(win_ptr, deal_key, (void *)0);
//	draw_line(mlx_ptr, win_ptr, p0, p1);
	draw_projection(proj_map, map_info);
	mlx_loop(mlx_ptr);*/
	return (0);
}
