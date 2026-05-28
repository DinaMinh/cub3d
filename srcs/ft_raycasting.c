/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 11:59:27 by dminh             #+#    #+#             */
/*   Updated: 2026/05/28 09:38:22 by dminh            ###   ########.fr       */
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
	i = 0;
	while (i < longest)
	{
		ft_pixel_put(game, x / M_SCALE, y / M_SCALE, PINK);
		x += (game->ray.x - game->player.pos_x) / longest;
		y += (game->ray.y - game->player.pos_y) / longest; 
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
	}
	else if (game->ray.t_h < game->ray.t_v)
	{
		game->ray.x = game->ray.hx;
		game->ray.y = game->ray.hy;
		game->ray.dist = game->ray.t_h * cos(game->player.angle - game->ray.angle);
	}
}

void	ft_draw_walls(t_game *game)
{
	float	start_y;
	float	temp_y;
	int		x;
	int		temp_x;
	int		i;
	int		j;
	int		width;

	start_y = 360 - (game->ray.line_h / 2);
	width = 1280 / 64;
	i = 0;
	temp_y = start_y;
	x = game->ray.r * width;
	while (i < game->ray.line_h)
	{
		j = 0;
		temp_x = x;
		while (j < width)
		{
			ft_pixel_put(game, temp_x, temp_y, PINK);
			temp_x++;
			j++;
		}
		i++;
		temp_y++;
	}
}

void	ft_draw_rays(t_game *game)
{
	ft_memset(&game->ray, 0, sizeof(game->ray));
	game->ray.angle = game->player.angle - DR * 30;
	game->ray.max_dof = game->map.width + game->map.height;
	if (game->ray.angle < 0)
		game->ray.angle += 2 * M_PI;
	else if (game->ray.angle > 2 * M_PI)
		game->ray.angle -= 2 * M_PI;
	while (game->ray.r < 64)
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
		ft_draw_line(game);
		game->ray.line_h = TILES * 720 / game->ray.dist;
		if (game->ray.line_h > 720)
			game->ray.line_h = 720;
		ft_draw_walls(game);
		game->ray.r++;
		game->ray.angle += DR;
		if (game->ray.angle < 0)
			game->ray.angle += 2 * M_PI;
		else if (game->ray.angle > 2 * M_PI)
			game->ray.angle -= 2 * M_PI;
	}
}
