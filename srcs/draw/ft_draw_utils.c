/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 10:48:11 by dminh             #+#    #+#             */
/*   Updated: 2026/06/15 17:37:29 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (y < 0 || y >= W_HEIGHT || x < 0 || x >= W_WIDTH)
		return ;
	dst = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_pixel_put_map(t_game *game, int x, int y, int color)
{
	char	*dst;
	int		sq_dist;

	if (y < 0 || y > 2 * CENTER_Y || x < 0 || x > CENTER_X * 2)
		return ;
	sq_dist = (x - CENTER_X) * (x - CENTER_X) + (y - CENTER_Y) * (y - CENTER_Y);
	if (sq_dist > (95 * 95))
		return ;
	dst = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_get_delta(t_game *game)
{
	game->delta_x = CENTER_X - game->player.pos_x / M_SCALE;
	game->delta_y = CENTER_Y - game->player.pos_y / M_SCALE;
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
