/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 15:55:35 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/02/01 16:38:12 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIN_HEIGHT 1200
# define WIN_WIDTH 1200
# define MARGIN 100
# define BUFFER_SIZE 100

# define MENU_COLOR 0xDDDDDD

# define WIDTH fdf->map_info.width
# define DEPTH fdf->map_info.depth
# define XMIN fdf->map_info.xmin
# define XMAX fdf->map_info.xmax
# define YMIN fdf->map_info.ymin
# define YMAX fdf->map_info.ymax
# define SCALE fdf->map_info.scale
# define PROJ fdf->map_info.proj
# define ZMAX fdf->map_info.zmax
# define ZMIN fdf->map_info.zmin
# define X_OFFSET fdf->map_info.x_offset
# define Y_OFFSET fdf->map_info.y_offset

# define DIR_INCR 20

typedef enum	e_proj
{
	ISOMETRIC,
	PARALLEL,
	TOP
}				t_proj;

typedef enum	e_color
{
	ALTITUDE,
	MAP,
	RAINBOW,
	MONO
}				t_color;

typedef struct	s_point
{
	double	x;
	double	y;
	double	z;
	int		color;
}				t_point;

typedef struct	s_map
{
	int		width;
	int		depth;
	double	xmax;
	double	xmin;
	double	ymax;
	double	ymin;
	int		zmax;
	int		zmin;
	double	scale;
	int		x_offset;
	int		y_offset;
	double	alt_ratio;
	t_proj	proj;
	t_color	color_scheme;
	double	alpha;
	double	beta;
	double	gamma;
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

void			command_menu(t_fdf fdf);

void			rotate_x(double *y, double *z, double alpha);
void			rotate_y(double *x, double *z, double beta);
void			rotate_z(double *x, double *y, double gamma);
void			calc_iso(t_fdf *fdf, int i, int j);
void			calc_para(t_fdf *fdf, int i, int j);

void			error(char *str, t_fdf *fdf);
void			free_2d_int_tab(int ***tab, int len);
void			free_2d_tpoint_tab(t_point ***tab, int len);
void			clear_fdf(t_fdf *fdf);

int				reader(char *file_name, t_fdf *fdf);
int				projection(t_fdf *fdf);
void			get_placement_info(t_fdf *fdf);
void			apply_colors(t_fdf *fdf);
int				gradient(t_fdf *fdf, t_point p, t_point p1, t_point p2);

int				new_image(t_fdf *fdf);
void			draw_image(t_fdf *fdf);

int				red_cross_closing(t_fdf *fdf);
int				key_press(int key, t_fdf *fdf);
void			event_move(int key, t_map *map_info);
void			event_zoom(int key, t_map *map_info);
void			event_adjust_alt(int key, t_map *map_info);
void			event_reset(t_fdf *fdf);
void			event_rainbow(t_fdf *fdf);
int				key_release(int key, t_fdf *fdf);


#endif
