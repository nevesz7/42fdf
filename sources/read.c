/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 23:06:04 by rarobert          #+#    #+#             */
/*   Updated: 2022/10/13 13:05:38 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// static void	**ft_free_array(char **split)
// {
// 	while (*split)
// 	{
// 		free(*split);
// 		split++;
// 	}
// 	return (NULL);
// }

int	get_columns(char *map_path)
{
	int		fd;
	int		columns;
	char	*line;
	size_t	i;

	i = 0;
	columns = 1;
	fd = open(map_path, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
		return (0);
	while (line[i] == ' ')
		i++;
	while (line[++i] && line[i] != '\n')
		if (line[i] != ' ' && line[i - 1] == ' ')
			columns++;
	free(line);
	close(fd);
	return (columns);
}

t_map	get_map(char *map_path, t_map map)
{
	char			*line;
	char			**split_line;
	size_t			i;
	int				fd;

	i = 0;
	map.columns = get_columns(map_path);
	map.lines = 0;
	fd = open(map_path, O_RDONLY);
	while (i >= 0)
	{
		line = get_next_line(fd);
		if (line)
		{
			split_line = ft_split(line, ' ');
			map.lines += save_line(split_line, &map, map.columns);
		}
		else
			break ;
		free (line);
		i++;
	}
	free(map_path);
	close(fd);
	return (map);
}

int	save_line(char **line, t_map *map, int columns)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (line[i])
	{
		map->last->color = 0;
		j = 0;
		if (line[i][j] == '\n')
			break ;
		map->last->x = map->last->position % columns;
		map->last->y = map->last->position / columns;
		map->last->z = ft_atoi(line[i]);
		while (line[i][++j])
			if (line[i][j] == ',')
				map->last->color = get_color(&line[i][j + 3]);
		map->last->p = create_point(map->last->x, map->last->y,
				map->last->z, map->last->color);
		map->last->next = new_map_node(map->last->position);
		map->last = map->last->next;
		i++;
	}
	ft_free_array(line, (void *)line);
	return (1);
}

int	get_color(char *hex)
{
	char	*hex_tab;
	size_t	i;
	size_t	j;
	int		nb;
	int		color;

	j = -1;
	nb = pow(16, ft_strlen(hex) - 1);
	color = 0;
	if (ft_strchr(hex, 'A') || ft_strchr(hex, 'B') || ft_strchr(hex, 'C')
		|| ft_strchr(hex, 'D') || ft_strchr(hex, 'E') || ft_strchr(hex, 'F'))
		hex_tab = "0123456789ABCDEF";
	else
		hex_tab = "0123456789abcdef";
	while (++j < ft_strlen(hex))
	{
		i = 0;
		while (hex[j] != hex_tab[i])
			i++;
		color += nb * i;
		nb = nb / 16;
	}
	return (color);
}
