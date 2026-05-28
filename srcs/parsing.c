
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

void	skip_spaces(char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
}



int	is_texture(char *str)
{
	if (!ft_strncmp(str, "NO ", 3) || !ft_strncmp(str, "SO ", 3)
		|| !ft_strncmp(str, "WE ", 3) || !ft_strncmp(str, "EA ", 3))
		return (1);
	return (0);
}

int	is_color(char *str)
{
	if (!ft_strncmp(str, "F ", 2) || !ft_strncmp(str, "C ", 2))
		return (1);
	return (0);
}

int	is_empty_or_whitespace(char *str)
{
	int	i;

	i = 0;
	skip_spaces(str, &i);
	if (str[i] == '\0' || str[i] == '\n')
		return (1);
	return (0);
}

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
		free(path);
		return (NULL);
	}
	close(fd);
	return (path);
}

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
		color[i] = ft_atoi(rgb[i]);
		if (color[i] < 0 || color[i] > 255)
			return (-1);
		i++;
	}
	if (i != 3)
		return (-1);
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
	//free_tab(rgb);
	if (color == -1)
		return (0);
	if (line[0] == 'F' && map->floor_color == -1)
		map->floor_color = color;
	else if (line[0] == 'C' && map->ceiling_color == -1)
		map->ceiling_color = color;
	else
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

int	parse_map_line(char *line, t_map *map)
{
	char	*clean_line;
	t_list	*new_node;

	if (!all_elements_loaded(map))
		return (0);
	if (map->empty_line_seen == 1)
		return (0);
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
			return (0); //free les lignes precedente 
		tmp = tmp->next;
		i++;
	}
	map->grid[i] = NULL; //free raw_map
	return (1);
}

int	is_floor_or_player(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	check_neighbors(t_map *map, int y, int x)
{
	if (y == 0 || y == map->height - 1 || x == 0 || x == map->width - 1)
		return (0);
	if (map->grid[y - 1][x] == ' ' || map->grid[y + 1][x] == ' ')
		return (0);
	if (map->grid[y][x - 1] == ' ' || map->grid[y][x + 1] == ' ')
		return (0);
	return (1);
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
			if (is_floor_or_player(map->grid[y][x]))
			{
				if (check_neighbors(map, y, x)== 0)
				{
					printf("ok");
					return (0);
				}
				if (map->grid[y][x] != '0')
					player_count++;
			}
		}
	}
	if (player_count != 1)
	{
		printf("test");
		return (0);
	}
	printf("COUCOU");
	return (1);
}
void	print_map_struct(t_map *map, char *step)
{
	printf("--- Structure t_map (%s) ---\n", step);
	printf("NO: %s\n", map->no_tex_path);
	printf("SO: %s\n", map->so_tex_path);
	printf("WE: %s\n", map->we_tex_path);
	printf("EA: %s\n", map->ea_tex_path);
	printf("Floor: %d\n", map->floor_color);
	printf("Ceiling: %d\n", map->ceiling_color);
	printf("Width: %d | Height: %d\n", map->width, map->height);
	printf("--------------------------------\n\n");
}

void	print_map_grid(t_map *map)
{
	int	i;

	printf("--- Grille Paddée finale ---\n");
	if (!map->grid)
	{
		printf("(Grille vide)\n\n");
		return ;
	}
	i = 0;
	while (map->grid[i])
	{
		printf("[%s]\n", map->grid[i]);
		i++;
	}
	printf("----------------------------\n\n");
}
//
//int	main(int ac, char **av)
//{
//	print_map_struct(&map, "Après remplissage :)");
//	print_map_grid(&map);
//	return (0);
//}
