/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_movements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 10:11:35 by dminh             #+#    #+#             */
/*   Updated: 2026/06/12 12:12:57 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_down(t_game *game)
{
	int	x;
	int	y;
	int	xo;
	int	yo;

	x = game->player.pos_x / (float)TILES;
	y = game->player.pos_y / (float)TILES;
	xo = (game->player.pos_x - game->player.dir_x * SPEED) / TILES;
	yo = (game->player.pos_y - game->player.dir_y * SPEED) / TILES;
	if (game->map.grid[y][xo] == '0' || game->map.grid[y][xo] == 'O')
		game->player.pos_x -= game->player.dir_x * SPEED;
	if (game->map.grid[yo][x] == '0' || game->map.grid[yo][x] == 'O')
		game->player.pos_y -= game->player.dir_y * SPEED;
}

void	ft_up(t_game *game)
{
	int	x;
	int	y;
	int	xo;
	int	yo;

	x = game->player.pos_x / (float)TILES;
	y = game->player.pos_y / (float)TILES;
	xo = (game->player.pos_x + game->player.dir_x * SPEED) / TILES;
	yo = (game->player.pos_y + game->player.dir_y * SPEED) / TILES;
	if (game->map.grid[y][xo] == '0' || game->map.grid[y][xo] == 'O')
		game->player.pos_x += game->player.dir_x * SPEED;
	if (game->map.grid[yo][x] == '0' || game->map.grid[yo][x] == 'O')
		game->player.pos_y += game->player.dir_y * SPEED;
}

void	ft_left(t_game *game)
{
	int	x;
	int	y;
	int	xo;
	int	yo;

	x = game->player.pos_x / (float)TILES;
	y = game->player.pos_y / (float)TILES;
	xo = (game->player.pos_x + game->player.dir_y * SPEED) / TILES;
	yo = (game->player.pos_y - game->player.dir_x * SPEED) / TILES;
	if (game->map.grid[y][xo] == '0' || game->map.grid[y][xo] == 'O')
		game->player.pos_x += game->player.dir_y * SPEED;
	if (game->map.grid[yo][x] == '0' || game->map.grid[yo][x] == 'O')
		game->player.pos_y -= game->player.dir_x * SPEED;
}

void	ft_right(t_game *game)
{
	int	x;
	int	y;
	int	xo;
	int	yo;

	x = game->player.pos_x / (float)TILES;
	y = game->player.pos_y / (float)TILES;
	xo = (game->player.pos_x - game->player.dir_y * SPEED) / TILES;
	yo = (game->player.pos_y + game->player.dir_x * SPEED) / TILES;
	if (game->map.grid[y][xo] == '0' || game->map.grid[y][xo] == 'O')
		game->player.pos_x -= game->player.dir_y * SPEED;
	if (game->map.grid[yo][x] == '0' || game->map.grid[yo][x] == 'O')
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
