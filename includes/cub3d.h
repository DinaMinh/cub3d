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

#endif
