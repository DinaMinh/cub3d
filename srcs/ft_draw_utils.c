/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 10:48:11 by dminh             #+#    #+#             */
/*   Updated: 2026/06/09 10:50:48 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (y < 0 || y > W_HEIGHT || x < 0 || x > W_WIDTH)
		return ;
	dst = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_pixel_put_map(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (y < 0 || y > 250 || x < 0 || x > 250)
		return ;
	dst = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_get_delta(t_game *game, int x, int y)
{
	int	delta_x;
	int	delta_y;

	delta_x = x * TILES - game->player.pos_x;
	delta_y = y * TILES - game->player.pos_y;
	game->screen_x = CENTER_X + (delta_x / M_SCALE);
	game->screen_y = CENTER_Y + (delta_y / M_SCALE);
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
