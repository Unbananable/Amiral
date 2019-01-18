/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 17:51:55 by anleclab          #+#    #+#             */
/*   Updated: 2019/01/18 18:38:55 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mlx.h"
#include "fdf.h"
#include "libft/includes/libft.h"
#include "libft/includes/ft_printf.h"

int		deal_mouse(int button, int x, int y, void *param)
{
	t_win	*win;

	win = (t_win *)param;
	if (param == NULL)
		return (0);
	ft_printf("Mouse key: %d, x: %d, y: %d\n", button, x, y);
	mlx_pixel_put(win->mlx_ptr, win->win_ptr, x, y, 0xffdd75);
	return (0);
}

int		deal_key(int key, void *param)
{
//Action qui se déroule à chaque input clavier (on peut par exemple print la
//touche (key) utilisée et s'en servir pour la relier à des actions définies
	key +=0;
	param +=0;
	ft_putstr("Key: ");
	ft_putnbr(key);
	ft_putchar('\n');
	if (key == 53)
		exit(1);
/*	if (key >= 123 || key <= 126)
		camera_arrow(key,...); //camera_top, camera_bot, camera_right, camera_left
	if (key == 4 || key == 5 || key == 24 || key == 27 || key == 69 || key == 78)
		camera_lense(key,...); //camera_zoom, camera_unzoom (+: 69 24 4) (-: 78 27 5)
	if (key == ? -Make a choice-)
		color_panel(key,...); //Several sets of colors, depending of the key ('1'(key 18) to '5'(key 23) for example)
	if (key == 35 ('P'))
		switch_projection(); //Switch between the 2 projections (+ affichage graphique du nom de la projection ?)
	if (key == 8 ('C'))
		activation_colours(); //Activation/désactivation des couleurs (une touche pour activer les couleurs et une touche pour les desactiver ou sinon il faut un interrupteur (var static ?) pour mémoriser si les couleurs sont actuellement affichées ou non)
*/	return (0);
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
	proj_map = top_projection(map, &map_info);
	draw_in_win(win, proj_map, map_info);
	mlx_key_hook(win.win_ptr, deal_key, (void *)0);
	mlx_mouse_hook(win.win_ptr, deal_mouse, &win);
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
	mlx_loop(mlx_ptr);*/
	return (0);
}
