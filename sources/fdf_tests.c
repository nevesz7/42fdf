/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_tests.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 12:09:03 by rarobert          #+#    #+#             */
/*   Updated: 2022/10/10 17:35:47 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			get_maps_info(char *path);
void			draw_circle(void *addr, int x, int y, int r);
t_map			get_map_info(int fd);
void			show_map(t_map map);

// void	draw_circle(void *addr, int xc, int yc, int r)
// {
// 	void	*window;
// 	t_mlx	circle;
// 	int		x;
// 	int		y;
// 	int		*rr;

// 	x = xc - r;
// 	y = yc - r;
// 	rr = malloc(9 * sizeof(int));
// 	rr[0] = r * 1 / 10;
// 	rr[1] = r * 2 / 10;
// 	rr[2] = r * 3 / 10;
// 	rr[3] = r * 4 / 10;
// 	rr[4] = r * 5 / 10;
// 	rr[5] = r * 6 / 10;
// 	rr[6] = r * 7 / 10;
// 	rr[7] = r * 8 / 10;
// 	rr[8] = r * 9 / 10;
// 	window = mlx_new_window(addr, 1024, 720, "circle");
// 	image.img = mlx_new_image(addr, 1024, 720);
// 	image.addr = mlx_get_data_addr(image.img, &image.bpp,
// 			&image.line_len, &image.endian);
// 	my_mlx_pixel_put(&image, xc, yc, 0x00FFFFFF);
// 	while (x <= xc + r)
// 	{
// 		y = yc - r;
// 		while (y <= yc + r)
// 		{
// 			if ((x - xc) * (x - xc) + (y - yc) * (y - yc) == r * r)
// 			{
// 				printf("x = %d, y = %d\n", x, y);
// 				my_mlx_pixel_put(&image, x, y, 0x00530000);
// 			}
// 			else if ((x - xc) * (x - xc) + (y - yc) * (y - yc) < r * r)
// 				my_mlx_pixel_put(&image, x, y, 0x000D5300);
// 			if ((x - xc) * (x - xc) + (y - yc) * (y - yc) < r[8] * r[8])
// 				my_mlx_pixel_put(&image, x, y, 0x001CB6BD);
// 			if ((x - xc) * (x - xc) + (y - yc) * (y - yc) < r[7] * r[7])
// 				my_mlx_pixel_put(&image, x, y, 0x000D5300);
// 			if ((x - xc) * (x - xc) + (y - yc) * (y - yc) < r[6] * r[6])
// 				my_mlx_pixel_put(&image, x, y, 0x001CB6BD);
// 			if ((x - xc) * (x - xc) + (y - yc) * (y - yc) < r[5] * r[5])
// 				my_mlx_pixel_put(&image, x, y, 0x000D5300);
// 			if ((x - xc) * (x - xc) + (y - yc) * (y - yc) < r[4] * r[4])
// 				my_mlx_pixel_put(&image, x, y, 0x001CB6BD);
// 			if ((x - xc) * (x - xc) + (y - yc) * (y - yc) < r[3] * r[3])
// 				my_mlx_pixel_put(&image, x, y, 0x000D5300);
// 			if ((x - xc) * (x - xc) + (y - yc) * (y - yc) < r[2] * r[2])
// 				my_mlx_pixel_put(&image, x, y, 0x001CB6BD);
// 			if ((x - xc) * (x - xc) + (y - yc) * (y - yc) < r[1] * r[1])
// 				my_mlx_pixel_put(&image, x, y, 0x000D5300);
// 			if ((x - xc) * (x - xc) + (y - yc) * (y - yc) < r[1] * r[1])
// 				my_mlx_pixel_put(&image, x, y, 0x001CB6BD);
// 			y++;
// 		}
// 		x++;
// 	}
// 	mlx_put_image_to_window(addr, window, image.img, 0, 0);
// 	mlx_loop(addr);
// 	free(rr);
// }

void	get_maps_info(char *path)
{
	char	*archive;
	char	**maps;
	size_t	i;
	size_t	j;
	int		fd;
	int		mapf;
	int		x;
	t_map	map;

	x = 0;
	maps = malloc(sizeof(maps) * 20);
	mapf = open("maps_info.txt", O_WRONLY);
	while (x < 21)
	{
		maps[x] = malloc(20);
		x++;
	}
	maps[0] = "basictest.fdf";
	maps[1] = "10-2.fdf";
	maps[2] = "plat.fdf";
	maps[3] = "elem.fdf";
	maps[4] = "10-70.fdf";
	maps[5] = "pnp_flat.fdf";
	maps[6] = "elem-col.fdf";
	maps[7] = "pentenegpos.fdf";
	maps[8] = "42.fdf";
	maps[9] = "elem2.fdf";
	maps[10] = "20-60.fdf";
	maps[11] = "pyramide.fdf";
	maps[12] = "pyra.fdf";
	maps[13] = "pylone.fdf";
	maps[14] = "50-4.fdf";
	maps[15] = "100-6.fdf";
	maps[16] = "mars.fdf";
	maps[17] = "t2.fdf";
	maps[18] = "t1.fdf";
	maps[19] = "julia.fdf";
	maps[20] = "elem-fract.fdf";
	i = 0;
	while (i < 21)
	{	
		write(1, "p", 1);
		j = 0;
		archive = malloc(1000);
		ft_strlcpy(archive, path, 800);
		ft_strlcat(archive, &maps[i][0], 800);
		fd = open(archive, O_RDONLY);
		while (maps[i][j] != '.')
		{
			write(mapf, &maps[i][j], 1);
			j++;
		}
		write (mapf, " has ", 5);
		write (mapf, ft_itoa(map.columns), ft_strlen(ft_itoa(map.columns)));
		write (mapf, " columns and ", 13);
		write (mapf, ft_itoa(map.lines), ft_strlen(ft_itoa(map.lines)));
		close (fd);
		free(archive);
		i++;
		write (mapf, " lines.\n", 8);
	}
}

t_map	get_map_info(int fd)
{
	char	*line;
	size_t	i;
	t_map	map;

	line = get_next_line(fd);
	map.columns = 1;
	i = 0;
	while (line[i] == ' ')
		i++;
	while (line[++i] && line[i] != '\n')
		if (line[i] != ' ' && line[i - 1] == ' ')
			map.columns++;
	map.lines = 1;
	while (line)
	{
		free (line);
		line = get_next_line(fd);
		if (line)
			map.lines++;
	}
	return (map);
}

void	show_map(t_map map)
{
	while (map.start->next)
	{
		ft_printf("%d ", map.start->z);
		if (map.start->position % map.columns == (map.columns - 1))
			ft_printf("\n");
		map.start = map.start->next;
	}
	ft_printf("\n");
}
