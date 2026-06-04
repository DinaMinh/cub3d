/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_movements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 10:11:35 by dminh             #+#    #+#             */
/*   Updated: 2026/06/04 12:29:51 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_down(t_game *game)
{
	int	x;
	int	y;
	int	xo;
	int	yo;

	x = game->player.pos_x / 64.0;
	y = game->player.pos_y / 64.0;
	xo = (game->player.pos_x - game->player.dir_x * SPEED) / 64;
	yo = (game->player.pos_y - game->player.dir_y * SPEED)  / 64;
	if (game->map.grid[y][xo] == '0')
		game->player.pos_x -= game->player.dir_x * SPEED;
	if (game->map.grid[yo][x] == '0')
		game->player.pos_y -= game->player.dir_y * SPEED;
}

void	ft_up(t_game *game)
{
	int	x;
	int	y;
	int	xo;
	int	yo;

	x = game->player.pos_x / 64.0;
	y = game->player.pos_y / 64.0;
	xo = (game->player.pos_x + game->player.dir_x * SPEED) / 64;
	yo = (game->player.pos_y + game->player.dir_y * SPEED)  / 64;
	if (game->map.grid[y][xo] == '0')
		game->player.pos_x += game->player.dir_x * SPEED;
	if (game->map.grid[yo][x] == '0')
		game->player.pos_y += game->player.dir_y * SPEED;
}

void	ft_left(t_game *game)
{
	int	x;
	int	y;
	int	xo;
	int	yo;

	x = game->player.pos_x / 64.0;
	y = game->player.pos_y / 64.0;
	xo = (game->player.pos_x + game->player.dir_y * SPEED) / 64;
	yo = (game->player.pos_y - game->player.dir_x * SPEED)  / 64;
	if (game->map.grid[y][xo] == '0')
		game->player.pos_x += game->player.dir_y * SPEED;
	if (game->map.grid[yo][x] == '0')
		game->player.pos_y -= game->player.dir_x * SPEED;
}

void	ft_right(t_game *game)
{
	int	x;
	int	y;
	int	xo;
	int	yo;

	x = game->player.pos_x / 64.0;
	y = game->player.pos_y / 64.0;
	xo = (game->player.pos_x - game->player.dir_y * SPEED) / 64;
	yo = (game->player.pos_y + game->player.dir_x * SPEED)  / 64;
	if (game->map.grid[y][xo] == '0')
		game->player.pos_x -= game->player.dir_y * SPEED;
	if (game->map.grid[yo][x] == '0')
		game->player.pos_y += game->player.dir_x * SPEED;
}

void	ft_movements(int keysym, t_game *game)
{
	ft_memset(game->addr, 0, 720 * game->line_length);
	game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel, \
			&game->line_length, &game->endian);
	if (keysym == XK_S || keysym == XK_s)
		ft_down(game);
	else if (keysym == XK_W || keysym == XK_w)
		ft_up(game);
	else if (keysym == XK_A || keysym == XK_a)
		ft_left(game);
	else if (keysym == XK_D || keysym == XK_d)
		ft_right(game);
	else if (keysym == XK_Left || keysym == XK_Right)
		ft_camera(keysym, game);
	ft_draw_map(game);
	ft_draw_rays(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img, 0, 0);
}
