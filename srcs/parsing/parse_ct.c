/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebourdet <ebourdet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 13:13:22 by ebourdet          #+#    #+#             */
/*   Updated: 2026/06/26 08:46:18 by ebourdet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_texture(char *line, t_map *map)
{
	char	*path;

	path = get_valid_path(line + 2);
	if (!path)
		return (0);
	if (!ft_strncmp(line, "NO", 2) && !map->no_tex_path)
		map->no_tex_path = path;
	else if (!ft_strncmp(line, "SO", 2) && !map->so_tex_path)
		map->so_tex_path = path;
	else if (!ft_strncmp(line, "WE", 2) && !map->we_tex_path)
		map->we_tex_path = path;
	else if (!ft_strncmp(line, "EA", 2) && !map->ea_tex_path)
		map->ea_tex_path = path;
	else
	{
		ft_putstr_fd("Error\nTexture en trop ou identifiant invalide\n", 2);
		free(path);
		return (0);
	}
	return (1);
}

int	parse_cub(char *filename, t_map *map)
{
	int	fd;
	int	status;

	init_map_struct(map);
	if (!check_extension(filename, ".cub"))
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	status = process_lines(fd, map);
	close(fd);
	return (status);
}

int	parse_rgb(char **rgb)
{
	int	i;
	int	color[3];

	i = 0;
	while (rgb[i])
	{
		if (i > 2)
		{
			ft_putstr_fd("Error\nFormat RGB invalide, trop de valeurs\n", 2);
			return (-1);
		}
		color[i] = ft_atoi(rgb[i]);
		if (color[i] < 0 || color[i] > 255)
		{
			ft_putstr_fd("Error\nValeur RGB hors limites (0-255)\n", 2);
			return (-1);
		}
		i++;
	}
	if (i != 3)
	{
		ft_putstr_fd("Error\nFormat RGB invalide (valeurs manquantes)\n", 2);
		return (-1);
	}
	return ((color[0] << 16) | (color[1] << 8) | color[2]);
}

int	parse_color(char *line, t_map *map)
{
	char	**rgb;
	int		color;

	rgb = ft_split(line + 1, ',');
	if (!rgb)
		return (0);
	color = parse_rgb(rgb);
	free_tab(rgb);
	if (color == -1)
		return (0);
	if (line[0] == 'F' && map->floor_color == -1)
		map->floor_color = color;
	else if (line[0] == 'C' && map->ceiling_color == -1)
		map->ceiling_color = color;
	else
	{
		ft_putstr_fd("Error\nCouleur en trop ou identifiant invalide\n", 2);
		return (0);
	}
	return (1);
}

int	parse_map_line(char *line, t_map *map)
{
	char	*clean_line;
	t_list	*new_node;

	if (!all_elements_loaded(map))
	{
		ft_putstr_fd("Error\nÉlément manquant avant la map\n", 2);
		return (0);
	}
	if (map->empty_line_seen == 1)
	{
		ft_putstr_fd("Error\nLigne vide au milieu de la map\n", 2);
		return (0);
	}
	map->map_started = 1;
	clean_line = dup_without_newline(line);
	if (!clean_line)
		return (0);
	new_node = ft_lstnew(clean_line);
	if (!new_node)
	{
		free(clean_line);
		return (0);
	}
	ft_lstadd_back(&map->raw_map, new_node);
	return (1);
}
