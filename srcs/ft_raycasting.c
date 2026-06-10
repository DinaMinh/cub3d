/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 11:59:27 by dminh             #+#    #+#             */
/*   Updated: 2026/06/10 10:10:07 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_init_rays(t_game *game)
{
	game->ray.hx = game->player.pos_x;
	game->ray.hy = game->player.pos_y;
	game->ray.vx = game->player.pos_x;
	game->ray.vy = game->player.pos_y;
	game->ray.t_h = MASSIVE;
	game->ray.t_v = MASSIVE;
	game->ray.a_tan = -1/tan(game->ray.angle);
	game->ray.n_tan = -tan(game->ray.angle);
	game->ray.dof = 0;
}

static void	ft_check_closest_ray(t_game *game)
{
	if (game->ray.t_v < game->ray.t_h)
	{
		game->ray.x = game->ray.vx;
		game->ray.y = game->ray.vy;
		game->ray.dist = game->ray.t_v * cos(game->player.angle - game->ray.angle);
		game->ray.color = PINK;
		game->ray.hit_side = VERTICAL;
	}
	else if (game->ray.t_h < game->ray.t_v)
	{
		game->ray.x = game->ray.hx;
		game->ray.y = game->ray.hy;
		game->ray.dist = game->ray.t_h * cos(game->player.angle - game->ray.angle);
		game->ray.color = DARKPINK;
		game->ray.hit_side = HORIZONTAL;
	}
}

void	ft_raycasting(t_game *game)
{
	float	step;
	float	tex_y;
	int		tex_x;

	step = (float)TILES / game->ray.line_h;
	tex_y = 0;
	if (game->ray.hit_side == VERTICAL)
	{
		if (game->ray.angle > M_PI / 2 && game->ray.angle < 3 * M_PI / 2)
			game->curr_tex = &game->west;
		else
			game->curr_tex = &game->east;
		tex_x = (int)game->ray.y % (TILES);
	}
	else if (game->ray.hit_side == HORIZONTAL)
	{
		if (game->ray.angle > M_PI)
			game->curr_tex = &game->north;
		else
			game->curr_tex = &game->south;
		tex_x = (int)game->ray.x % (TILES);
	}
	ft_draw_walls(game, tex_x, tex_y, step);
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
		game->ray.stored_x[game->ray.r] = game->ray.x;
		game->ray.stored_y[game->ray.r] = game->ray.y;
		game->ray.line_h = TILES * W_HEIGHT / game->ray.dist;
		ft_raycasting(game);
		game->ray.r++;
		game->ray.angle += game->ray.angle_step;
		if (game->ray.angle < 0)
			game->ray.angle += 2 * M_PI;
		else if (game->ray.angle > 2 * M_PI)
			game->ray.angle -= 2 * M_PI;
	}
}

void	ft_draw_rays(t_game *game)
{
	ft_memset(&game->ray, 0, sizeof(game->ray));
	ft_get_fov(game);
	game->ray.angle = game->player.angle - (game->ray.fov / 2);
	game->ray.max_dof = game->map.width + game->map.height;
	if (game->ray.angle < 0)
		game->ray.angle += 2 * M_PI;
	else if (game->ray.angle > 2 * M_PI)
		game->ray.angle -= 2 * M_PI;
	ft_raycasting_loop(game);
}
