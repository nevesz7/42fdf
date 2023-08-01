/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 03:38:43 by rarobert          #+#    #+#             */
/*   Updated: 2022/12/30 01:33:05 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char *argv[])
{
	char	*map_path;
	t_mlx	fdf;

	if (argc != 2)
		return (error(PARAMETER_ERROR));
	map_path = ft_strjoin("maps/", argv[1]);
	if (open(map_path, O_CLOEXEC) == -1)
	{
		free(map_path);
		return (error(FILE_ERROR));
	}
	fdf.mlx = mlx_init();
	fdf.map = new_map();
	*fdf.map = get_map(map_path, *fdf.map);
	fdf.image = create_image(fdf.mlx);
	fdf.window = mlx_new_window(fdf.mlx, WIDTH, HEIGHT, argv[1]);
	adjust(fdf.map, &fdf.image);
	mlx_expose_hook(fdf.window, &refresh_image, &fdf);
	mlx_key_hook(fdf.window, &key_hook, &fdf);
	mlx_hook(fdf.window, 17, 0, &close_window, &fdf);
	mlx_loop(fdf.mlx);
	return (0);
}

int	error(int error_code)
{
	if (error_code == PARAMETER_ERROR)
	{
		write(1, "Parameter error!\n", 17);
		write(1, "Use: ./fdf map_name\n", 20);
	}
	if (error_code == FILE_ERROR)
	{
		write(1, "Invalid map_name, try one of these:\n", 36);
		write(1, "10-2.fdf 10-70.fdf 20-60.fdf 50-4.fdf 100-6.fdf\n", 48);
		write(1, "42.fdf basictest.fdf plat.fdf pnp_flat.fdf\n", 43);
		write(1, "pyra.fdf pyramide.fdf pylone.fdf pentenegpos.fdf\n", 49);
		write(1, "mars.fdf t1.fdf t2.fdf julia.fdf elem-fract.fdf\n", 48);
		write(1, "elem.fdf elem2.fdf elem-col.fdf\n", 32);
		write(1, "julia.fdf elem-fract.fdf\n", 25);
	}
	return (0);
}
