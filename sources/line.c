/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 04:43:25 by rarobert          #+#    #+#             */
/*   Updated: 2022/11/13 03:22:14 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(void *image, t_point a, t_point b)
{
	int	delta_x;
	int	delta_y;
	int	color;

	if (a.color && a.color > b.color)
		color = a.color;
	if (b.color && b.color >= a.color)
		color = b.color;
	if (a.color == 0 && b.color == 0 && a.z != b.z)
		color = 13070910;
	if (a.color == 0 && b.color == 0 && a.z == b.z && a.z == 0)
		color = 9835026;
	if (a.color == 0 && b.color == 0 && a.z == b.z && a.z != 0)
		color = 14683539;
	delta_x = a.x - b.x;
	delta_y = a.y - b.y;
	if (b.x > a.x)
		delta_x = b.x - a.x;
	if (b.y > a.y)
		delta_y = b.y - a.y;
	if (delta_x >= delta_y)
		draw_line_util_1(image, a, b, color);
	else
		draw_line_util_2(image, a, b, color);
}

void	draw_line_util_1(void *image, t_point a, t_point b, int color)
{
	int	*delta;
	int	decision;

	my_mlx_pixel_put(image, a.x, a.y, color);
	delta = get_delta(a, b);
	decision = (2 * delta[1]) - delta[0];
	while (a.x != b.x)
	{
		a.x = a.x + delta[2];
		if (decision <= 0)
		{
			decision += (2 * delta[1]);
			my_mlx_pixel_put(image, a.x, a.y, color);
		}
		else
		{
			decision += 2 * (delta[1] - delta[0]);
			a.y = a.y + delta[3];
			my_mlx_pixel_put(image, a.x, a.y, color);
		}
	}
	my_mlx_pixel_put(image, b.x, b.y, color);
	free(delta);
}

void	draw_line_util_2(void *image, t_point a, t_point b, int color)
{
	int	*delta;
	int	decision;

	my_mlx_pixel_put(image, a.x, a.y, color);
	delta = get_delta(a, b);
	decision = (2 * delta[0]) - delta[1];
	while (a.y != b.y)
	{
		a.y = a.y + delta[3];
		if (decision <= 0)
		{
			decision += (2 * delta[0]);
			my_mlx_pixel_put(image, a.x, a.y, color);
		}
		else
		{
			decision += 2 * (delta[0] - delta[1]);
			a.x = a.x + delta[2];
			my_mlx_pixel_put(image, a.x, a.y, color);
		}
	}
	my_mlx_pixel_put(image, b.x, b.y, color);
	free(delta);
}

// delta[0] = absolute value of x1 - x2
// delta[1] = absolute value of y1 - y2
// delta[2] = 1 if x2>x1, -1 if x1>x2
// delta[3] = 1 if y2>y1, -1 if y1>y2
int	*get_delta(t_point a, t_point b)
{
	int	*delta;

	delta = malloc(4 * sizeof(int));
	if (b.x > a.x)
	{
		delta[2] = 1;
		delta[0] = b.x - a.x;
	}
	else
	{
		delta[2] = -1;
		delta[0] = a.x - b.x;
	}
	if (b.y > a.y)
	{
		delta[3] = 1;
		delta[1] = b.y - a.y;
	}
	else
	{
		delta[3] = -1;
		delta[1] = a.y - b.y;
	}
	return (delta);
}

t_point	create_point(int x, int y, int z, int color)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.z = z;
	point.color = color;
	return (point);
}
 