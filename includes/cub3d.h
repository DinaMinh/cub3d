/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebourdet <ebourdet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 13:47:31 by dminh             #+#    #+#             */
/*   Updated: 2026/05/27 13:49:04 by ebourdet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include "mlx.h"
# include "libft.h"

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	char	*no_tex_path;
	char	*so_tex_path;
	char	*we_tex_path;
	char	*ea_tex_path;
	int		floor_color;
	int		ceiling_color;
	t_list	*raw_map;
	int		map_started;
	int		empty_line_seen;
}	t_map;

void	init_map_struct(t_map *map);
int		check_extension(char *filename, char *ext);
void	skip_spaces(char *line, int *i);
int		route_line(char *line, t_map *map);
int		is_texture(char *str);
int		is_color(char *str);
int		is_empty_or_whitespace(char *str);
int		process_lines(int fd, t_map *map);
char	*get_valid_path(char *str);
int		parse_texture(char *line, t_map *map);
int		parse_cub(char *filename, t_map *map);
int		parse_rgb(char **rgb);
int		parse_color(char *line, t_map *map);
int		all_elements_loaded(t_map *map);
char	*dup_without_newline(char *line);
int		parse_map_line(char *line, t_map *map);
int		get_max_width(t_list *raw_map);
char	*pad_line(char *raw_line, int max_width);
int		build_final_map(t_map *map);
int		is_floor_or_player(char c);
int		check_neighbors(t_map *map, int y, int x);
int		validate_map_walls(t_map *map);
void	print_map_struct(t_map *map, char *step);
void	print_map_grid(t_map *map);

#endif
