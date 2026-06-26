/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebourdet <ebourdet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 13:13:05 by ebourdet          #+#    #+#             */
/*   Updated: 2026/06/26 08:46:10 by ebourdet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_neighbors(t_map *map, int y, int x)
{
	if (y == 0 || y == map->height - 1 || x == 0 || x == map->width - 1)
		return (0);
	if (map->grid[y - 1][x] == ' ' || map->grid[y + 1][x] == ' '
			|| !is_valid_char(map->grid[y - 1][x])
			|| !is_valid_char(map->grid[y + 1][x]))
		return (0);
	if (map->grid[y][x - 1] == ' ' || map->grid[y][x + 1] == ' '
			|| !is_valid_char(map->grid[y][x - 1])
			|| !is_valid_char(map->grid[y][x + 1]))
		return (0);
	return (1);
}

int	all_elements_loaded(t_map *map)
{
	if (map->no_tex_path && map->so_tex_path
		&& map->we_tex_path && map->ea_tex_path
		&& map->floor_color != -1 && map->ceiling_color != -1)
		return (1);
	return (0);
}

int	check_extension(char *filename, char *ext)
{
	int	len;
	int	ext_len;

	if (!filename || !ext)
		return (0);
	len = ft_strlen(filename);
	ext_len = ft_strlen(ext);
	if (len <= ext_len)
		return (0);
	if (ft_strncmp(filename + len - ext_len, ext, ext_len) == 0)
		return (1);
	return (0);
}

int	is_floor_or_player(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == 'D')
		return (1);
	return (0);
}

int	validate_map_walls(t_map *map)
{
	int	y;
	int	x;
	int	player_count;

	y = -1;
	player_count = 0;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (!is_valid_char(map->grid[y][x]) && map->grid[y][x] != ' ')
				return (msg_err("Caractère invalide dans la map\n"));
			if (is_floor_or_player(map->grid[y][x]))
			{
				if (check_neighbors(map, y, x) == 0)
					return (msg_err("Mur manquant\n"));
				if (map->grid[y][x] != '0' && map->grid[y][x] != 'D')
					player_count++;
			}
		}
	}
	if (player_count != 1)
		return (msg_err("Nombre de joueurs invalide (1 requis)\n"));
	return (1);
}
