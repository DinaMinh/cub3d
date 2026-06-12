/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 10:45:17 by dminh             #+#    #+#             */
/*   Updated: 2026/06/12 13:22:39 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_draw_square(t_game *game, int x, int y, int width)
{
	int	i;
	int	j;

	i = 0;
	while (i < width)
	{
		j = 0;
		while (j < width)
		{
			ft_pixel_put(game, x + j, y + i, YELLOW);
			j++;
		}
		i++;
	}
}

void	ft_draw_map(t_game *game)
{
	int	y;

	y = 0;
	ft_get_delta(game);
	while (game->map.grid[y])
	{
		ft_minimap_loop(game, y);
		y++;
	}
	ft_draw_square(game, CENTER_X - (PLAYER_W / 2),
		CENTER_Y - (PLAYER_W / 2), PLAYER_W);
	ft_draw_minimap_rays(game);
}

void	ft_draw_line(t_game *game)
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

void	ft_draw_walls(t_game *game, int tex_x, float tex_y, float step)
{
	float	start_y;
	float	end_y;

	start_y = W_HEIGHT / 2 - (game->ray.line_h / 2);
	if (start_y < 0)
	{
		tex_y = fabs(start_y) * step;
		start_y = 0;
	}
	end_y = W_HEIGHT / 2 + (game->ray.line_h / 2);
	if (end_y > W_HEIGHT)
		end_y = W_HEIGHT;
	while (start_y < end_y)
	{
		game->ray.color = ft_pixel_color(game->curr_tex, tex_x, (int)tex_y);
		if (game->ray.color != 0x00000000)
			ft_pixel_put(game, game->ray.r, (int)start_y, game->ray.color);
		start_y++;
		tex_y += step;
	}
}
