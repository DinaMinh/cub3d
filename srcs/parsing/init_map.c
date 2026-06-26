/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebourdet <ebourdet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 13:13:10 by ebourdet          #+#    #+#             */
/*   Updated: 2026/06/26 08:46:04 by ebourdet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map_struct(t_map *map)
{
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
	map->no_tex_path = NULL;
	map->so_tex_path = NULL;
	map->we_tex_path = NULL;
	map->ea_tex_path = NULL;
	map->floor_color = -1;
	map->ceiling_color = -1;
}

char	*get_valid_path(char *str)
{
	int		i;
	int		j;
	char	*path;
	int		fd;

	i = 0;
	j = 0;
	skip_spaces(str, &i);
	while (str[i + j] && str[i + j] != ' ' && str[i + j] != '\n')
		j++;
	path = ft_substr(str, i, j);
	if (!path)
		return (NULL);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nFichier texture introuvable/inouvrable\n", 2);
		free(path);
		return (NULL);
	}
	close(fd);
	return (path);
}

char	*dup_without_newline(char *line)
{
	int		len;
	char	*new_line;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	new_line = ft_substr(line, 0, len);
	return (new_line);
}

int	is_valid_char(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == 'D'
		|| c == '1')
		return (1);
	return (0);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
