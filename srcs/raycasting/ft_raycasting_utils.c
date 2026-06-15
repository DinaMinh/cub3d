/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 17:04:19 by dminh             #+#    #+#             */
/*   Updated: 2026/06/15 10:41:17 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	ft_dist(t_game *game, float x, float y)
{
	return (sqrt((x - game->player.pos_x) * (x - game->player.pos_x)
			+ (y - game->player.pos_y) * (y - game->player.pos_y)));
}

void	ft_check_hori(t_game *game)
{
	if (game->ray.angle == 0 || fabs(game->ray.angle - M_PI) < DIFF)
	{
		game->ray.x = game->player.pos_x;
		game->ray.y = game->player.pos_y;
		game->ray.dof = game->ray.max_dof;
	}
	else if (game->ray.angle > M_PI)
	{
		game->ray.y = (((int)game->player.pos_y >> TILE_SHIFT)
				<< TILE_SHIFT) - DIFF;
		game->ray.x = (game->player.pos_y - game->ray.y) * game->ray.a_tan
			+ game->player.pos_x;
		game->ray.y_offset = -TILES;
		game->ray.x_offset = -game->ray.y_offset * game->ray.a_tan;
	}
	else if (game->ray.angle < M_PI)
	{
		game->ray.y = (((int)game->player.pos_y >> TILE_SHIFT)
				<< TILE_SHIFT) + TILES;
		game->ray.x = (game->player.pos_y - game->ray.y) * game->ray.a_tan
			+ game->player.pos_x;
		game->ray.y_offset = TILES;
		game->ray.x_offset = -game->ray.y_offset * game->ray.a_tan;
	}
}

void	ft_check_vert(t_game *game)
{
	if (fabs(game->ray.angle - M_PI / 2) < DIFF
		|| fabs(game->ray.angle - 3 * M_PI / 2) < DIFF)
	{
		game->ray.x = game->player.pos_x;
		game->ray.y = game->player.pos_y;
		game->ray.dof = game->ray.max_dof;
	}
	else if (game->ray.angle > M_PI / 2 && game->ray.angle < 3 * M_PI / 2)
	{
		game->ray.x = (((int)game->player.pos_x >> TILE_SHIFT)
				<< TILE_SHIFT) - DIFF;
		game->ray.y = (game->player.pos_x - game->ray.x) * game->ray.n_tan
			+ game->player.pos_y;
		game->ray.x_offset = -TILES;
		game->ray.y_offset = -game->ray.x_offset * game->ray.n_tan;
	}
	else if (game->ray.angle < M_PI / 2 || game->ray.angle > 3 * M_PI / 2)
	{
		game->ray.x = (((int)game->player.pos_x >> TILE_SHIFT)
				<< TILE_SHIFT) + TILES;
		game->ray.y = (game->player.pos_x - game->ray.x) * game->ray.n_tan
			+ game->player.pos_y;
		game->ray.x_offset = TILES;
		game->ray.y_offset = -game->ray.x_offset * game->ray.n_tan;
	}
}

void	ft_check_hori_ray(t_game *game)
{
	game->ray.mx = (int)(game->ray.x) >> TILE_SHIFT;
	game->ray.my = (int)(game->ray.y) >> TILE_SHIFT;
	if (game->ray.mx >= 0 && game->ray.mx < game->map.width
		&& game->ray.my >= 0 && game->ray.my < game->map.height)
	{
		if (game->map.grid[game->ray.my][game->ray.mx] == '1'
				|| game->map.grid[game->ray.my][game->ray.mx] == 'D')
		{
			game->ray.hx = game->ray.x;
			game->ray.hy = game->ray.y;
			game->ray.t_h = ft_dist(game, game->ray.hx, game->ray.hy);
			game->ray.dof = game->ray.max_dof;
		}
		else if (game->map.grid[game->ray.my][game->ray.mx] == 'O')
			ft_set_door_hori_rays(game);
		else
		{
			game->ray.x += game->ray.x_offset;
			game->ray.y += game->ray.y_offset;
			game->ray.dof++;
		}
	}
	else
		game->ray.dof = game->ray.max_dof;
}

void	ft_check_vert_ray(t_game *game)
{
	game->ray.mx = (int)(game->ray.x) >> TILE_SHIFT;
	game->ray.my = (int)(game->ray.y) >> TILE_SHIFT;
	if (game->ray.mx >= 0 && game->ray.mx < game->map.width
		&& game->ray.my >= 0 && game->ray.my < game->map.height)
	{
		if (game->map.grid[game->ray.my][game->ray.mx] == '1'
			|| game->map.grid[game->ray.my][game->ray.mx] == 'D')
		{
			game->ray.vx = game->ray.x;
			game->ray.vy = game->ray.y;
			game->ray.t_v = ft_dist(game, game->ray.vx, game->ray.vy);
			game->ray.dof = game->ray.max_dof;
		}
		else if (game->map.grid[game->ray.my][game->ray.mx] == 'O')
			ft_set_door_vert_rays(game);
		else
		{
			game->ray.x += game->ray.x_offset;
			game->ray.y += game->ray.y_offset;
			game->ray.dof++;
		}
	}
	else
		game->ray.dof = game->ray.max_dof;
}
