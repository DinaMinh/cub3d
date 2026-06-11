/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebourdet <ebourdet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 13:13:19 by ebourdet          #+#    #+#             */
/*   Updated: 2026/06/11 13:35:24 by ebourdet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	route_line(char *line, t_map *map)
{
	int	i;

	i = 0;
	if (is_empty_or_whitespace(line))
	{
		if (map->map_started == 1)
			map->empty_line_seen = 1;
		return (1);
	}
	skip_spaces(line, &i);
	if (is_texture(&line[i]))
		return (parse_texture(&line[i], map));
	else if (is_color(&line[i]))
		return (parse_color(&line[i], map));
	else if (line[i] == '1' || line[i] == '0')
		return (parse_map_line(line, map));
	return (0);
}

int	process_lines(int fd, t_map *map)
{
	char	*line;
	int		status;

	status = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (status == 1)
			status = route_line(line, map);
		free(line);
	}
	return (status);
}

int	get_max_width(t_list *raw_map)
{
	int		max;
	int		len;
	t_list	*tmp;

	max = 0;
	tmp = raw_map;
	while (tmp)
	{
		len = ft_strlen((char *)tmp->content);
		if (len > max)
			max = len;
		tmp = tmp->next;
	}
	return (max);
}

char	*pad_line(char *raw_line, int max_width)
{
	char	*padded;
	int		len;
	int		i;

	padded = malloc(sizeof(char) * (max_width + 1));
	if (!padded)
		return (NULL);
	len = ft_strlen(raw_line);
	i = -1;
	while (++i < len)
		padded[i] = raw_line[i];
	while (i < max_width)
	{
		padded[i] = ' ';
		i++;
	}
	padded[max_width] = '\0';
	return (padded);
}

int	build_final_map(t_map *map)
{
	t_list	*tmp;
	int		i;

	map->height = ft_lstsize(map->raw_map);
	map->width = get_max_width(map->raw_map);
	map->grid = malloc(sizeof(char *) * (map->height + 1));
	if (!map->grid)
		return (0);
	tmp = map->raw_map;
	i = 0;
	while (tmp)
	{
		map->grid[i] = pad_line((char *)tmp->content, map->width);
		if (!map->grid[i])
			return (0);
		tmp = tmp->next;
		i++;
	}
	map->grid[i] = NULL;
	return (1);
}
