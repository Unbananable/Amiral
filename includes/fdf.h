/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 15:55:35 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/01/28 17:12:28 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "keys.h"

# define WIN_HEIGHT 1200
# define WIN_WIDTH 1200
# define MARGIN 100
# define BUFFER_SIZE 100

# define WIDTH map_info->width
# define DEPTH map_info->depth
# define XMIN map_info->xmin
# define XMAX map_info->xmax
# define YMIN map_info->ymin
# define YMAX map_info->ymax
# define SCALE map_info->scale

typedef enum	e_proj
{
	ISOMETRIC,
	PARALLEL,
	TOP
}				t_proj;

typedef struct	s_point
{
	double	x;
	double	y;
	int		colour;
}				t_point;

typedef struct	s_map
{
	int		width;
	int		depth;
	double	xmax;
	double	xmin;
	double	ymax;
	double	ymin;
	double	scale;
	int		x_offset;
	int		y_offset;
	double	alt_ratio;
	t_proj	proj;
}				t_map;

typedef struct	s_image
{
	int		bpp;
	int		size_line;
	int		endian;
}				t_image;

typedef struct	s_fdf
{
	unsigned int	*addr;
	int				**map;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	t_point			**proj_map;
	t_map			map_info;
	t_image			image;
}				t_fdf;

void			error(char *str);

int				**reader(char *file_name, t_map *map_info);
t_point			**projection(t_proj proj, int **map, t_map *map_info);
t_point			**parallel_projection(int **map, t_map *map_info);
t_point			**isometric_projection(int **map, t_map *map_info);
t_point			**top_projection(int **map, t_map *map_info);
void			get_placement_info(t_point **proj_map, t_map *map_info);

void			new_image(t_fdf *fdf);
void			draw_image(t_fdf *fdf);

int				red_cross_closing(void *param);
int				key_press(int key, t_fdf *fdf);
void			event_move(int key, t_map *map_info);
void			event_zoom(int key, t_map *map_info);
void			event_adjust_alt(int key, t_map *map_info);
int				key_release(int key, t_fdf *fdf);

#endif
