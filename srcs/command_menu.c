/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_menu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 12:23:19 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/02/01 14:16:30 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"

void	command_menu(t_fdf fdf)
{
	int	y;

	y = 0;
	mlx_string_put(fdf.mlx_ptr, fdf.win_ptr, 50, y += 10, MENU_COLOR, "Command Repertory:");
	mlx_string_put(fdf.mlx_ptr, fdf.win_ptr, 10, y += 15, MENU_COLOR, "______________________________________");
	mlx_string_put(fdf.mlx_ptr, fdf.win_ptr, 10, y += 25, MENU_COLOR, "| - Altitude: Up/Down Arrows         |");
	mlx_string_put(fdf.mlx_ptr, fdf.win_ptr, 10, y += 25, MENU_COLOR, "| - Zoom in: +                       |");
	mlx_string_put(fdf.mlx_ptr, fdf.win_ptr, 10, y += 25, MENU_COLOR, "| - Zoom out: -                      |");
	mlx_string_put(fdf.mlx_ptr, fdf.win_ptr, 10, y += 25, MENU_COLOR, "| - Up/Down/Left/Right: W/S/A/D      |");
	mlx_string_put(fdf.mlx_ptr, fdf.win_ptr, 10, y += 20, MENU_COLOR, "|   Diagonal movements : Q/E/Z/X     |");
	mlx_string_put(fdf.mlx_ptr, fdf.win_ptr, 10, y += 25, MENU_COLOR, "| - Rotations:                       |");
	mlx_string_put(fdf.mlx_ptr, fdf.win_ptr, 10, y += 20, MENU_COLOR, "|        X-Axis: 2 / 8 (NUMPAD)      |");
	mlx_string_put(fdf.mlx_ptr, fdf.win_ptr, 10, y += 20, MENU_COLOR, "|        Y-Axis: 4 / 6 (NUMPAD)      |");
	mlx_string_put(fdf.mlx_ptr, fdf.win_ptr, 10, y += 20, MENU_COLOR, "|        Z-Axis: 1-3 / 7-9 (NUMPAD)  |");
	mlx_string_put(fdf.mlx_ptr, fdf.win_ptr, 10, y += 25, MENU_COLOR, "| - Projections:                     |");
	mlx_string_put(fdf.mlx_ptr, fdf.win_ptr, 10, y += 20, MENU_COLOR, "|        Top: T                      |");
	mlx_string_put(fdf.mlx_ptr, fdf.win_ptr, 10, y += 20, MENU_COLOR, "|        Isometric: I                |");
	mlx_string_put(fdf.mlx_ptr, fdf.win_ptr, 10, y += 20, MENU_COLOR, "|        Parallel: P                 |");
	mlx_string_put(fdf.mlx_ptr, fdf.win_ptr, 10, y += 10, MENU_COLOR, "______________________________________");
}
