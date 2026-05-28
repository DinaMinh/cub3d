/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 13:47:31 by dminh             #+#    #+#             */
/*   Updated: 2026/05/27 11:53:54 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include "mlx.h"
# include "libft.h"

# define TILES 64
# define M_TILES 16
# define M_SCALE 4
# define PLAYER_W 2.5
# define SPEED 5
# define YELLOW 0x00FFFF00
# define RED 0x00CC3300
# define WHITE 0x00FFFFFF
# define PURPLE 0x00666699
# define PINK 0x00FF66FF
# define PI2 M_PI / 2
# define PI3 3 * M_PI / 2
# define DR 0.0174533
# define MASSIVE 1000000
# define NORTH 4.712
# define SOUTH 1.571
# define WEST M_PI
# define EAST 0

extern char	map[6][11];

typedef struct s_ray
{
	float	x;
	float	y;
	float	hx;
	float	hy;
	float	t_h;
	float	vx;
	float	vy;
	float	t_v;
	float	dist;
	float	angle;
	float	x_offset;
	float	y_offset;
	float	a_tan;
	float	n_tan;
	float	line_h;
	float	line_o;
	int		r;
	int		mx;
	int		my;
	int		dof;
	int		max_dof;
}	t_ray;

typedef struct s_player
{
	float	pos_x;
	float	pos_y;
	float	dir_x;
	float	dir_y;
	float	angle;
	//float	plane_x;
	//float	plane_y;
}	t_player;

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

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_player	player;
	t_map		map;
	t_ray		ray;
}	t_game;

int		ft_input(int keysym, t_game *game);
void	ft_movements(int keysym, t_game *game);
void	ft_draw_map(t_game *game);
void	ft_draw_angle(t_game *game);
void	ft_draw_square(t_game *game, int x, int y, int width);
void	ft_camera(int keysym, t_game *game);
void	ft_pixel_put(t_game *game, int x, int y, int color);
void	ft_draw_rays(t_game *game);
float	ft_dist(t_game *game, float x, float y);
void	ft_check_hori(t_game *game);
void	ft_check_vert(t_game *game);
void	ft_check_hori_ray(t_game *game);
void	ft_check_vert_ray(t_game *game);
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
