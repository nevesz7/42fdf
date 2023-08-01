/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 01:03:57 by rarobert          #+#    #+#             */
/*   Updated: 2022/10/08 11:57:32 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <fcntl.h>
# include "libft.h"
# include "math.h"
# define ZERO 48
# define UM 49
# define DOIS 50
# define TRES 51
# define QUATRO 52
# define CINCO 53
# define SEIS 54
# define SETE 55
# define OITO 56
# define NOVE 57
# define Q 113
# define W 119
# define E 101
# define R 114
# define T 116
# define Y 121
# define U 117
# define I 105
# define O 111
# define P 112
# define A 97
# define S 115
# define D 100
# define F 102
# define G 103
# define LEFT 65361
# define UP 65362
# define RIGHT 65363
# define DOWN 65364
# define ESC 65307
# define PARAMETER_ERROR 666
# define FILE_ERROR 777

# ifndef WIDTH
#  define WIDTH 1280
# endif

# ifndef HEIGHT
#  define HEIGHT 720
# endif

typedef struct s_point {
	int	x;
	int	y;
	int	z;
	int	color;
}				t_point;

typedef struct s_map_values {
	int					position;
	int					x;
	int					y;
	int					z;
	int					color;
	t_point				p;
	struct s_map_values	*next;
}				t_map_values;

typedef struct s_map {
	int					lines;
	int					columns;
	int					xy_scale;
	int					z_scale;
	int					min_x;
	int					min_y;
	struct s_map_values	*start;
	struct s_map_values	*last;
}				t_map;

typedef struct s_image {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}				t_image;

typedef struct s_mlx {
	void	*mlx;
	void	*window;
	t_map	*map;
	t_image	image;
}				t_mlx;

//draw
int				*get_delta(t_point a, t_point b);
void			print_map(t_map map, void *image);
void			draw_line(void *addr, t_point a, t_point b);
void			draw_line_util_1(void *image, t_point a, t_point b, int color);
void			draw_line_util_2(void *image, t_point a, t_point b, int color);
void			my_mlx_pixel_put(t_image *image, int x, int y, int color);

//map_struct
t_map			*new_map(void);
void			free_map(t_map *map);
t_map_values	*new_map_node(int position);
t_point			create_point(int x, int y, int z, int color);

//mlx
t_image			create_image(void *addr);
void			clear_window(void *image);
int				close_window(t_mlx *fdf);
int				refresh_image(t_mlx *fdf);
int				key_hook(int keycode, t_mlx *fdf);

//read
int				error(int error_code);
t_map			get_map(char *map_path, t_map map);
int				get_color(char *hex_code);
int				get_columns(char *map_path);
int				save_line(char **line, t_map *map, int columns);

//projection
int				get_z(int z, int scale);
int				get_scale(int keycode);
void			adjust(t_map *map, void *image);
void			adjust_xy(int keycode, t_mlx *fdf);
void			adjust_z(int keycode, t_mlx *fdf, int signal);
t_point			get_iso(t_point point, int xy_scale, int z_scale);

#endif