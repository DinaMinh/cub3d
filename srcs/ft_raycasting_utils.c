/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 17:04:19 by dminh             #+#    #+#             */
/*   Updated: 2026/05/26 17:05:12 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	ft_dist(t_game *game, float x, float y)
{
	return (sqrt((x - game->player.pos_x) * (x - game->player.pos_x) \
				+ (y - game->player.pos_y) * (y - game->player.pos_y)));
}

void	ft_check_hori(t_game *game)
{
	if (game->ray.angle == 0 || game->ray.angle == M_PI)
	{
		printf("y = %f\n", game->ray.y);
		game->ray.x = game->player.pos_x;
		game->ray.y = game->player.pos_y;
		game->ray.dof = 6;
	}
	else if (game->ray.angle > M_PI)
	{
		game->ray.y = (((int)game->player.pos_y >> 6) << 6) - 0.0001;
		game->ray.x = (game->player.pos_y - game->ray.y) * game->ray.a_tan
			+ game->player.pos_x;
		game->ray.y_offset = -TILES;
		game->ray.x_offset = -game->ray.y_offset * game->ray.a_tan;
		
	}
	else if (game->ray.angle < M_PI)
	{
		game->ray.y = (((int)game->player.pos_y >> 6) << 6) + TILES;
		game->ray.x = (game->player.pos_y - game->ray.y) * game->ray.a_tan
			+ game->player.pos_x;
		game->ray.y_offset = TILES;
		game->ray.x_offset = -game->ray.y_offset * game->ray.a_tan;
	}
}

void	ft_check_vert(t_game *game)
{
	if (fabs(game->ray.angle - PI2) < 0.0001 || fabs(game->ray.angle - PI3) < 0.0001)
	{
		game->ray.x = game->player.pos_x;
		game->ray.y = game->player.pos_y;
		game->ray.dof = 6;
	}
	else if (game->ray.angle > PI2 && game->ray.angle < PI3)
	{
		game->ray.x = (((int)game->player.pos_x >> 6) << 6) - 0.0001;
		game->ray.y = (game->player.pos_x - game->ray.x) * game->ray.n_tan
			+ game->player.pos_y;
		game->ray.x_offset = -TILES;
		game->ray.y_offset = -game->ray.x_offset * game->ray.n_tan;
		
	}
	else if (game->ray.angle < PI2 || game->ray.angle > PI3)
	{
		game->ray.x = (((int)game->player.pos_x >> 6) << 6) + TILES;
		game->ray.y = (game->player.pos_x - game->ray.x) * game->ray.n_tan
			+ game->player.pos_y;
		game->ray.x_offset = TILES;
		game->ray.y_offset = -game->ray.x_offset * game->ray.n_tan;
	}
}

void	ft_check_hori_ray(t_game *game)
{
	game->ray.mx = (int)(game->ray.x) >> 6;
	game->ray.my = (int)(game->ray.y) >> 6;
	if (game->ray.mx >= 0 && game->ray.mx < 6
			&& game->ray.my >= 0 && game->ray.my < 6)
	{
		if (map[game->ray.my][game->ray.mx] == '1')
		{
			game->ray.hx = game->ray.x;
			game->ray.hy = game->ray.y;
			game->ray.t_h = ft_dist(game, game->ray.hx, game->ray.hy);
			game->ray.dof = 6;
		}
		else
		{
			game->ray.x += game->ray.x_offset;
			game->ray.y += game->ray.y_offset;
			game->ray.dof++;
		}
	}
	else
		game->ray.dof = 6;
}

void	ft_check_vert_ray(t_game *game)
{
	game->ray.mx = (int)(game->ray.x) >> 6;
	game->ray.my = (int)(game->ray.y) >> 6;
	if (game->ray.mx >= 0 && game->ray.mx < 6
			&& game->ray.my >= 0 && game->ray.my < 6)
	{
		if (map[game->ray.my][game->ray.mx] == '1')
		{
			game->ray.vx = game->ray.x;
			game->ray.vy = game->ray.y;
			game->ray.t_v = ft_dist(game, game->ray.vx, game->ray.vy);
			game->ray.dof = 6;
		}
		else
		{
			game->ray.x += game->ray.x_offset;
			game->ray.y += game->ray.y_offset;
			game->ray.dof++;
		}
	}
	else
		game->ray.dof = 6;
}
