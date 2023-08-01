/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:29:38 by rarobert          #+#    #+#             */
/*   Updated: 2022/10/04 03:36:52 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	get_iso(t_point point, int xy_scale, int z_scale)
{
	t_point	iso;
	int		x;
	int		y;
	int		z;

	x = point.x * xy_scale;
	y = point.y * xy_scale;
	iso.z = point.z;
	if (z_scale > 0)
		z = point.z * z_scale;
	if (z_scale < 0)
		z = get_z(point.z, z_scale * -1);
	iso.x = (x - y) * cos(0.523599);
	iso.y = (-z + (x + y)) * sin(0.523599);
	iso.color = point.color;
	return (iso);
}

int	get_z(int z, int scale)
{
	if (scale == 5)
		z = z / 5;
	if (scale == 10)
		z = z / 10;
	if (scale == 15)
		z = z / 15;
	if (scale == 20)
		z = z / 20;
	if (scale == 25)
		z = z / 25;
	return (z);
}

int	get_scale(int keycode)
{
	if (keycode == UM || keycode == Q)
		return (1);
	if (keycode == DOIS || keycode == W)
		return (2);
	if (keycode == TRES || keycode == E)
		return (3);
	if (keycode == QUATRO || keycode == R || keycode == A)
		return (5);
	if (keycode == CINCO || keycode == T)
		return (7);
	if (keycode == SEIS || keycode == Y || keycode == S)
		return (10);
	if (keycode == SETE || keycode == U || keycode == D)
		return (15);
	if (keycode == OITO || keycode == I || keycode == F)
		return (20);
	if (keycode == G)
		return (25);
	if (keycode == NOVE || keycode == O)
		return (30);
	if (keycode == ZERO || keycode == P)
		return (50);
	return (0);
}
