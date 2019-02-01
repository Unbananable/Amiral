/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 09:45:17 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/02/01 14:37:32 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "math.h"

void	rotate_x(double *y, double *z, double alpha)
{
	double	prev_y;

	prev_y = *y;
	*y = prev_y * cos(alpha) + *z * sin(alpha);
	*z = -prev_y * sin(alpha) + *z * cos(alpha);
}

void	rotate_y(double *x, double *z, double beta)
{
	double	prev_x;

	prev_x = *x;
	*x = prev_x * cos(beta) + *z * sin(beta);
	*z = -prev_x * sin(beta) + *z * cos(beta);
}

void	rotate_z(double *x, double *y, double gamma)
{
	double prev_x;
	double prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = prev_x * cos(gamma) - prev_y * sin(gamma);
	*y = prev_x * sin(gamma) + prev_y * cos(gamma);
}
