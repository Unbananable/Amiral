/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 15:55:35 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/02/08 12:10:17 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIN_HEIGHT 1200
# define WIN_WIDTH 1200
# define MARGIN 200
# define BUFFER_SIZE 4096

# define MENU_COLOR 0xDDDDDD
# define MOUSE_ROTATION_COEF 0.005
# define ANGLE_INCR 0.02
# define OFFSET_INCR 10
# define ZOOM_INCR 0.2
# define ALT_INCR 0.1

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
# define COLOR_SCHEME fdf->map_info.color_scheme

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
	FANCY_RAINBOW,
	MONO
}				t_color;

typedef struct	s_mouse
{
	int	pressed;
	int	last_x;
	int	last_y;
	int	x;
	int	y;

}				t_mouse;

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
	t_mouse			mouse;
	t_map			map_info;
	t_image			image;
	int				rainbow;
	int				printed;
}				t_fdf;

void			print_command_menu(t_fdf fdf);

void			reset_color(t_fdf *fdf);
void			rotate_x(double *y, double *z, double alpha);
void			rotate_y(double *x, double *z, double beta);
void			rotate_z(double *x, double *y, double gamma);
void			calc_iso(t_fdf *fdf, int i, int j);
void			calc_para(t_fdf *fdf, int i, int j);
void			calc_top(t_fdf *fdf, int i, int j);

void			error(char *str, t_fdf *fdf);
void			free_2d_int_tab(int ***tab, int len);
void			free_2d_tpoint_tab(t_point ***tab, int len);
void			clear_fdf(t_fdf *fdf);

int				reader(char *file_name, t_fdf *fdf);
int				projection(t_fdf *fdf);
void			get_placement_info(t_fdf *fdf);

int				gradient(t_fdf *fdf, t_point p, t_point p1, t_point p2);
double			percent(double current, double start, double end);
int				color_lvl(int start, int end, double ratio);
int				altitude_color(t_fdf *fdf, double z);
int				rainbow_color(t_fdf *fdf, t_point p);

int				new_image(t_fdf *fdf);
void			draw_image(t_fdf *fdf);

int				red_cross_closing(t_fdf *fdf);
int				key_press(int key, t_fdf *fdf);
void			event_move(int key, t_fdf *fdf);
void			event_zoom(int key, t_map *map_info);
void			event_rotate(int key, t_map *map_info);
void			event_adjust_alt(int key, t_map *map_info);
void			event_reset(t_fdf *fdf);
void			event_rainbow(t_fdf *fdf);
int				key_release(int key, t_fdf *fdf);
int				mouse_press(int button, int x, int y, t_fdf *fdf);
int				mouse_release(int button, int x, int y, t_fdf *fdf);
int				mouse_move(int x, int y, t_fdf *fdf);

int				is_valid_mapchar(char c);

#endif
