/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 13:47:31 by dminh             #+#    #+#             */
/*   Updated: 2026/06/10 11:12:47 by dminh            ###   ########.fr       */
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

# define W_WIDTH 1280
# define W_HEIGHT 720
# define MS 1000
# define FPS 60
# define CENTER_X 50
# define CENTER_Y 50
# define TILES 64
# define M_TILES 16
# define M_SCALE 4
# define PLAYER_W 2.5
# define SPEED 4
# define MOUSE_ROTATION 0.001
# define FOV 60

# define YELLOW 0x00FFFF00
# define RED 0x00CC3300
# define WHITE 0x00FFFFFF
# define PURPLE 0x00666699
# define PINK 0x00FF66FF
# define DARKPINK 0x00CC0099

# define MASSIVE 1000000
# define NORTH 4.712
# define SOUTH 1.571
# define WEST M_PI
# define EAST 0

# define HORIZONTAL true
# define VERTICAL false

typedef struct s_ray
{
	float	stored_x[W_WIDTH];
	float	stored_y[W_WIDTH];
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
	float	fov;
	float	angle_step;
	float	step_x;
	float	step_y;
	bool	hit_side;
	int		color;
	int		r;
	int		mx;
	int		my;
	int		dof;
	int		max_dof;
}	t_ray;

typedef enum	e_keys
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	L_ARROW,
	R_ARROW,
} t_keys;

typedef struct s_player
{
	float	pos_x;
	float	pos_y;
	float	dir_x;
	float	dir_y;
	float	angle;
	int		mouse_x;
	int		mouse_y;
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

typedef struct	s_textures
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}	t_textures;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img;
	int			key[6];
	char		*addr;
	float		screen_x;
	float		screen_y;
	int			delta_x;
	int			delta_y;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_player	player;
	t_map		map;
	t_ray		ray;
	t_textures	*curr_tex;
	t_textures	north;
	t_textures	south;
	t_textures	west;
	t_textures	east;

}	t_game;

unsigned int	ft_pixel_color(t_textures *texture, int x, int y);
long long		ft_get_time(void);
int				ft_input(int keysym, t_game *game);
int				ft_release(int keysym, t_game *game);
int				ft_click_cross(t_game *game);
int				ft_game_hook(t_game *game);
int				ft_clean_exit(t_game *game);
int				ft_game_hook(t_game *game);
void			ft_init_texture(t_game *game);
void			ft_pixel_put(t_game *game, int x, int y, int color);
void			ft_pixel_put_map(t_game *game, int x, int y, int color);
void			ft_get_delta(t_game *game);
void			ft_key_press(int keysym, t_game *game);
void			ft_key_release(int keysym, t_game *game);
void			ft_movements(t_game *game);
void			ft_starting_orientation(t_game *game);
void			ft_game(t_game *game);
void			ft_draw_map(t_game *game);
void			ft_draw_angle(t_game *game);
void			ft_draw_line(t_game *game);
void			ft_draw_walls(t_game *game, int tex_x, float tex_y, float step);
void			ft_draw_minimap_rays(t_game *game);
void			ft_draw_floor(t_game *game);
void			ft_get_fov(t_game *game);
void			ft_camera(int keysym, t_game *game);
void			ft_draw_rays(t_game *game);
float			ft_dist(t_game *game, float x, float y);
void			ft_check_hori(t_game *game);
void			ft_check_vert(t_game *game);
void			ft_check_hori_ray(t_game *game);
void			ft_check_vert_ray(t_game *game);
void			init_map_struct(t_map *map);
int				check_extension(char *filename, char *ext);
void			skip_spaces(char *line, int *i);
int				route_line(char *line, t_map *map);
int				is_texture(char *str);
int				is_color(char *str);
int				is_empty_or_whitespace(char *str);
int				process_lines(int fd, t_map *map);
char			*get_valid_path(char *str);
int				parse_texture(char *line, t_map *map);
int				parse_cub(char *filename, t_map *map);
int				parse_rgb(char **rgb);
int				parse_color(char *line, t_map *map);
int				all_elements_loaded(t_map *map);
char			*dup_without_newline(char *line);
int				parse_map_line(char *line, t_map *map);
int				get_max_width(t_list *raw_map);
char			*pad_line(char *raw_line, int max_width);
int				build_final_map(t_map *map);
int				is_floor_or_player(char c);
int				check_neighbors(t_map *map, int y, int x);
int				validate_map_walls(t_map *map);
void			print_map_struct(t_map *map, char *step);
void			print_map_grid(t_map *map);
void			ft_draw_minimap_rays(t_game *game);
void			ft_initial_mouse_pos(t_game *game);
int				ft_mouse(int x, int y, t_game *game);

#endif
