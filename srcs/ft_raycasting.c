/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 11:59:27 by dminh             #+#    #+#             */
/*   Updated: 2026/06/08 17:19:14 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_draw_line(t_game *game)
{
	float	x;
	float	y;
	float	i;
	float	longest;

	x = game->player.pos_x;
	y = game->player.pos_y;
	if (fabs(game->ray.x - x) < fabs(game->ray.y - y))
		longest = fabs(game->ray.y - y);
	else
		longest = fabs(game->ray.x - x);
	game->ray.step_x = (game->ray.x - game->player.pos_x) / longest;
	game->ray.step_y = (game->ray.y - game->player.pos_y) / longest;
	i = 0;
	while (i < longest)
	{
		ft_pixel_put_map(game, CENTER_X + ((x - game->player.pos_x) / M_SCALE),
				CENTER_Y + ((y - game->player.pos_y) / M_SCALE), PINK);
		x += game->ray.step_x;
		y += game->ray.step_y;
		i++;
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

void	ft_draw_walls(t_game *game, int tex_x, float tex_y, float step)
{
	float	start_y;
	int		i;

	i = 0;
	start_y = W_HEIGHT / 2 - (game->ray.line_h / 2);
	while (i < game->ray.line_h)
	{
		game->ray.color = ft_pixel_color(&game->west, tex_x, (int)tex_y);
		ft_pixel_put(game, game->ray.r, (int)start_y + i, game->ray.color);
		i++;
		tex_y += step;
	}
}

void	ft_get_fov(t_game *game)
{
	game->ray.fov = FOV * (M_PI / 180.0);
	game->ray.angle_step = game->ray.fov / W_WIDTH;
}

void	ft_draw_minimap_rays(t_game *game)
{
	int	i;

	i = 0;
	while (i < W_WIDTH)
	{
		if (!(i % 30))
		{
			game->ray.x = game->ray.stored_x[i];
			game->ray.y = game->ray.stored_y[i];
			ft_draw_line(game);
		}
		i++;
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
		if (game->ray.line_h > W_HEIGHT)
			game->ray.line_h = W_HEIGHT;
		float	step = 32.0 / game->ray.line_h;
		float	tex_y = 0;
		int		tex_x;
		if (game->ray.hit_side == VERTICAL)
			tex_x = (int)game->ray.y % TILES;
		else if (game->ray.hit_side == HORIZONTAL)
			tex_x = (int)game->ray.x % TILES;
		(void)step, (void)tex_y, (void)tex_x;
		ft_draw_walls(game, tex_x, tex_y, step);
		game->ray.r++;
		game->ray.angle += game->ray.angle_step;
		if (game->ray.angle < 0)
			game->ray.angle += 2 * M_PI;
		else if (game->ray.angle > 2 * M_PI)
			game->ray.angle -= 2 * M_PI;
	}
}
