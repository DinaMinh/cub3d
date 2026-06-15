/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_door.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 11:31:05 by dminh             #+#    #+#             */
/*   Updated: 2026/06/15 10:40:24 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_door_anim(t_game *game)
{
	long long	elapsed;

	game->d_anim.map_x = (int)game->ray.x >> TILE_SHIFT;
	game->d_anim.map_y = (int)game->ray.y >> TILE_SHIFT;
	elapsed = 0;
	if (game->d_anim.map_x >= 0 && game->d_anim.map_x < game->map.width
		&& game->d_anim.map_y >= 0 && game->d_anim.map_y < game->map.height)
	{
		if (game->map.grid[game->d_anim.map_y][game->d_anim.map_x] == 'D')
		{
			game->curr_tex = &game->door;
			if (game->d_anim.opening
				&& game->d_anim.map_x == game->d_anim.open_x
				&& game->d_anim.map_y == game->d_anim.open_y)
			{
				elapsed = ft_get_time() - game->d_anim.start_time;
				if (elapsed <= 150)
					game->curr_tex = &game->d_anim.frame1;
				else
					game->curr_tex = &game->d_anim.frame2;
			}
			else
				game->curr_tex = &game->door;
		}
	}
}

int	ft_check_door(t_game *game, int *tex_x)
{
	if (game->ray.draw_door)
	{
		game->curr_tex = &game->d_anim.frame2;
		if (game->ray.hit_side == VERTICAL)
		{
			if (game->ray.angle > M_PI / 2 && game->ray.angle < 3 * M_PI / 2)
				*tex_x = (TILES - 1) - ((int)game->ray.y % (TILES));
			else
				*tex_x = (int)game->ray.y % (TILES);
		}
		else
		{
			if (game->ray.angle > M_PI)
				*tex_x = (int)game->ray.x % (TILES);
			else
				*tex_x = (TILES - 1) - ((int)game->ray.x % (TILES));
		}
		return (1);
	}
	return (0);
}

void	ft_check_closest_ray_door(t_game *game)
{
	if (game->ray.door_t_v < game->ray.door_t_h)
	{
		game->ray.door_x = game->ray.door_vx;
		game->ray.door_y = game->ray.door_vy;
		game->ray.door_dist = game->ray.door_t_v
			* cos(game->player.angle - game->ray.angle);
		game->ray.door_hit_side = VERTICAL;
	}
	else if (game->ray.door_t_h <= game->ray.door_t_v)
	{
		game->ray.door_x = game->ray.door_hx;
		game->ray.door_y = game->ray.door_hy;
		game->ray.door_dist = game->ray.door_t_h
			* cos(game->player.angle - game->ray.angle);
		game->ray.door_hit_side = HORIZONTAL;
	}
}

void	ft_is_door(t_game *game)
{
	if (game->ray.is_door && game->ray.door_dist < game->ray.dist)
	{
		game->ray.line_h = TILES * W_HEIGHT / game->ray.door_dist;
		game->ray.x = game->ray.door_x;
		game->ray.y = game->ray.door_y;
		game->ray.hit_side = game->ray.door_hit_side;
		game->ray.draw_door = true;
		ft_raycasting(game);
	}
}
