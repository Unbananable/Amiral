/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 15:55:35 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/01/18 12:53:27 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIN_HEIGHT 500
# define WIN_WIDTH 500
# define MARGIN 20
# define BUFFER_SIZE 100

/*
 * typedef struct	s_camera ?? (Cookbook)
 * typedef struct	s_fdf ?? (Cookbook)
 */
typedef struct	s_point
{
	int		x;
	int		y;
	int		colour;
}				t_point;

typedef struct	s_map
{
	int		width;
	int		depth;
	int		scale;
	int		xmax;
	int		ymax;
	//Pour identifier les points de la map, on rajouterais pas un t_point **points ? (Idée)
}				t_map;

void	error(char *str);
void	draw_line(void *mlx_ptr, void *win_ptr, t_point p0, t_point p1);
void	draw_in_win(void *mlx_ptr, void *win_ptr, t_point **points, t_map map_info);
int		**reader(char *file_name, t_map *map_info);
t_point	**parallel_projection(int **map, t_map *map_info);

#endif
