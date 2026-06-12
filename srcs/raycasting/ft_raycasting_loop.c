/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting_loop.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 12:03:43 by dminh             #+#    #+#             */
/*   Updated: 2026/06/12 12:05:05 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_check_closest_ray(t_game *game)
{
	if (game->ray.t_v < game->ray.t_h)
	{
		game->ray.x = game->ray.vx;
		game->ray.y = game->ray.vy;
		game->ray.dist = game->ray.t_v
			* cos(game->player.angle - game->ray.angle);
		game->ray.hit_side = VERTICAL;
	}
	else if (game->ray.t_h <= game->ray.t_v)
	{
		game->ray.x = game->ray.hx;
		game->ray.y = game->ray.hy;
		game->ray.dist = game->ray.t_h
			* cos(game->player.angle - game->ray.angle);
		game->ray.hit_side = HORIZONTAL;
	}
}

void	ft_check_wall_face(t_game *game, int *tex_x)
{
	if (game->ray.hit_side == VERTICAL)
	{
		*tex_x = (int)game->ray.y % (TILES);
		if (game->ray.angle > M_PI / 2 && game->ray.angle < 3 * M_PI / 2)
		{
			game->curr_tex = &game->east;
			*tex_x = (TILES - 1) - ((int)game->ray.y % (TILES));
		}
		else
			game->curr_tex = &game->west;
	}
	else
	{
		*tex_x = (int)game->ray.x % (TILES);
		if (game->ray.angle > M_PI)
			game->curr_tex = &game->south;
		else
		{
			game->curr_tex = &game->north;
			*tex_x = (TILES - 1) - ((int)game->ray.x % (TILES));
		}
	}
}

static void	ft_init_rays(t_game *game)
{
	game->ray.hx = game->player.pos_x;
	game->ray.hy = game->player.pos_y;
	game->ray.vx = game->player.pos_x;
	game->ray.vy = game->player.pos_y;
	game->ray.t_h = MASSIVE;
	game->ray.t_v = MASSIVE;
	game->ray.a_tan = -1 / tan(game->ray.angle);
	game->ray.n_tan = -tan(game->ray.angle);
	game->ray.dof = 0;
	game->ray.is_door = false;
	game->ray.door_t_h = MASSIVE;
	game->ray.door_t_v = MASSIVE;
}

void	ft_raycasting_loop(t_game *game)
{
	while (game->ray.r < W_WIDTH)
	{
		ft_init_rays(game);
		ft_check_hori(game);
		while (game->ray.dof < game->ray.max_dof)
			ft_check_hori_ray(game);
		game->ray.dof = 0;
		ft_check_vert(game);
		while (game->ray.dof < game->ray.max_dof)
			ft_check_vert_ray(game);
		ft_check_closest_ray(game);
		ft_check_closest_ray_door(game);
		game->ray.stored_x[game->ray.r] = game->ray.x;
		game->ray.stored_y[game->ray.r] = game->ray.y;
		game->ray.line_h = TILES * W_HEIGHT / game->ray.dist;
		game->ray.draw_door = false;
		ft_raycasting(game);
		ft_is_door(game);
		game->ray.r++;
		game->ray.angle += game->ray.angle_step;
		if (game->ray.angle < 0)
			game->ray.angle += 2 * M_PI;
		else if (game->ray.angle > 2 * M_PI)
			game->ray.angle -= 2 * M_PI;
	}
}
