/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 08:44:00 by rarobert          #+#    #+#             */
/*   Updated: 2022/09/27 17:30:04 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map_values	*new_map_node(int position)
{
	t_map_values	*new;

	new = malloc(sizeof(t_map_values));
	new->position = position + 1;
	new->next = NULL;
	new->p.color = 0;
	return (new);
}

t_map	*new_map(void)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	map->start = new_map_node(-1);
	map->last = map->start;
	map->columns = 1;
	map->xy_scale = 1;
	map->z_scale = 1;
	return (map);
}

void	get_values(t_map *map)
{
	t_map_values	*node;

	node = map->start;
	while (node->next)
	{
		node->x = node->position % map->columns;
		node->y = node->position / map->columns;
		node = node->next;
	}
	node->x = node->position % map->columns;
	node->y = node->position / map->columns;
}

void	free_map(t_map *map)
{
	t_map_values	*aux;
	t_map_values	*this;

	aux = map->start;
	while (aux->next)
	{
		this = aux;
		aux = aux->next;
		free (this);
	}
	free (aux);
	free (map);
}

void	print_map(t_map map, void *image)
{
	t_map_values	*up;
	t_map_values	*it;

	up = map.start;
	it = map.start;
	while (it->next)
	{
		if (it->position > (map.columns - 1))
		{
			draw_line(image, up->p, it->p);
			up = up->next;
		}
		if (it->x != (map.columns - 1))
			draw_line(image, it->p, it->next->p);
		it = it->next;
	}
}
