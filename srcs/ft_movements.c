/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_movements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 10:11:35 by dminh             #+#    #+#             */
/*   Updated: 2026/06/08 13:33:04 by dminh            ###   ########.fr       */
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

void	ft_movements(t_game *game)
{
	if (game->key[UP] == 1)
		ft_up(game);
	if (game->key[DOWN] == 1)
		ft_down(game);
	if (game->key[LEFT] == 1)
		ft_left(game);
	if (game->key[RIGHT] == 1)
		ft_right(game);
	if (game->key[L_ARROW] == 1)
		ft_camera(XK_Left, game);
	if (game->key[R_ARROW] == 1)
		ft_camera(XK_Right, game);
}

void	ft_key_press(int keysym, t_game *game)
{
	if (keysym == XK_W || keysym == XK_w)
		game->key[UP] = 1;
	else if (keysym == XK_S || keysym == XK_s)
		game->key[DOWN] = 1;
	else if (keysym == XK_A || keysym == XK_a)
		game->key[LEFT] = 1;
	else if (keysym == XK_D || keysym == XK_d)
		game->key[RIGHT] = 1;
	else if (keysym == XK_Left)
		game->key[L_ARROW] = 1;
	else if (keysym == XK_Right)
		game->key[R_ARROW] = 1;
}

void	ft_key_release(int keysym, t_game *game)
{
	if (keysym == XK_W || keysym == XK_w)
		game->key[UP] = 0;
	else if (keysym == XK_S || keysym == XK_s)
		game->key[DOWN] = 0;
	else if (keysym == XK_A || keysym == XK_a)
		game->key[LEFT] = 0;
	else if (keysym == XK_D || keysym == XK_d)
		game->key[RIGHT] = 0;
	else if (keysym == XK_Left)
		game->key[L_ARROW] = 0;
	else if (keysym == XK_Right)
		game->key[R_ARROW] = 0;
}
