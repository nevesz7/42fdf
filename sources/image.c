/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 09:25:09 by rarobert          #+#    #+#             */
/*   Updated: 2022/10/13 02:35:48 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clear_window(void *image)
{
	int	x;
	int	y;

	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
			my_mlx_pixel_put(image, x, y, 0);
	}
}

int	close_window(t_mlx *fdf)
{
	free_map(fdf->map);
	mlx_destroy_window(fdf->mlx, fdf->window);
	mlx_destroy_image(fdf->mlx, fdf->image.img);
	mlx_destroy_display(fdf->mlx);
	free(fdf->mlx);
	exit (0);
}

int	refresh_image(t_mlx *fdf)
{
	mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->image.img, 0, 0);
	return (0);
}

t_image	create_image(void *addr)
{
	t_image	image;

	image.img = mlx_new_image(addr, WIDTH, HEIGHT);
	image.addr = mlx_get_data_addr(image.img, &image.bpp,
			&image.line_len, &image.endian);
	return (image);
}

void	my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	if (x > WIDTH || y > HEIGHT || x < 0 || y < 0)
		return ;
	dst = image->addr + (y * image->line_len + x * (image->bpp / 8));
	*(unsigned int *)dst = color;
}
