/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 01:31:16 by rarobert          #+#    #+#             */
/*   Updated: 2022/10/01 11:55:27 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_hook(int keycode, t_mlx *fdf)
{
	if (keycode == ESC)
		close_window(fdf);
	if (keycode >= ZERO && keycode <= NOVE)
		adjust_xy(get_scale(keycode), fdf);
	if (keycode == Q || keycode == W || keycode == E || keycode == R
		|| keycode == T || keycode == Y || keycode == U
		|| keycode == I || keycode == O || keycode == P)
		adjust_z(get_scale(keycode), fdf, 1);
	if (keycode == A || keycode == S || keycode == D
		|| keycode == F || keycode == G)
		adjust_z(get_scale(keycode), fdf, -1);
	return (0);
}

void	adjust_xy(int scale, t_mlx *fdf)
{
	fdf->map->xy_scale = scale;
	clear_window(&fdf->image);
	adjust(fdf->map, &fdf->image);
	mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->image.img, 0, 0);
}

void	adjust_z(int scale, t_mlx *fdf, int signal)
{
	fdf->map->z_scale = scale * signal;
	clear_window(&fdf->image);
	adjust(fdf->map, &fdf->image);
	mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->image.img, 0, 0);
}

void	adjust(t_map *map, void *image)
{
	t_map_values	*aux;

	aux = map->start;
	map->min_x = 0;
	map->min_y = 0;
	while (aux->next)
	{
		aux->p = get_iso(create_point(aux->x, aux->y, aux->z, aux->color),
				map->xy_scale, map->z_scale);
		if (aux->p.x < map->min_x)
			map->min_x = aux->p.x;
		if (aux->p.y < map->min_y)
			map->min_y = aux->p.y;
		aux = aux->next;
	}
	aux = map->start;
	while (aux)
	{
		aux->p.x -= map->min_x;
		aux->p.y -= map->min_y;
		aux = aux->next;
	}
	print_map(*map, image);
}
