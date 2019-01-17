/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 15:55:35 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/01/17 18:20:46 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIN_HEIGHT 500
# define WIN_WIDTH 500

typedef struct	s_point
{
	int		x;
	int		y;
}				t_point;

typedef struct	s_map
{
	int		width;
	int		depth;
	int		scale;
	int		xmax;
	int		ymax;
}				t_map;

void	draw_line(void *mlx_ptr, void *win_ptr, t_point p0, t_point p1);
int		**reader(char *file_name, t_map *map_info);

#endif
