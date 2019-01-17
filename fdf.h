/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 15:55:35 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/01/17 19:44:57 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIN_HEIGHT 500
# define WIN_WIDTH 500

/*
 * typedef struct	s_camera ?? (Cookbook)
 * typedef struct	s_fdf ?? (Cookbook)
 */
typedef struct	s_point
{
	int		x;
	int		y;
	int		z;
	//On peut aussi rajouter un int colour pour les options,
	//histoire d'associer un point à sa couleur ? (Idée)
}				t_point;

typedef struct	s_map
{
	int		width;
	int		depth;//heigth plutôt non ? vu qu'une profondeur ne peut qu'intervenir en 3D
	int		scale;
	int		xmax;
	int		ymax;
	//Pour identifier les points de la map, on rajouterais pas un t_point **points ? (Idée)
}				t_map;

void	draw_line(void *mlx_ptr, void *win_ptr, t_point p0, t_point p1);
int		**reader(char *file_name, t_map *map_info);

#endif
