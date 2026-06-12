/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 13:19:38 by dminh             #+#    #+#             */
/*   Updated: 2026/06/12 13:19:38 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_draw_square_map(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < M_TILES)
	{
		j = 0;
		while (j < M_TILES)
		{
			if (j == M_TILES - 1 || i == M_TILES - 1)
				ft_pixel_put_map(game, x + j, y + i, 0x00000000);
			else
				ft_pixel_put_map(game, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	ft_minimap_loop(t_game *game, int y)
{
	int	x;
	int	color;

	x = 0;
	while (game->map.grid[y][x])
	{
		game->screen_x = game->delta_x + x * M_TILES;
		game->screen_y = game->delta_y + y * M_TILES;
		if (game->map.grid[y][x] == '1')
			color = WHITE;
		else if (game->map.grid[y][x] == '0' || game->map.grid[y][x] == 'O')
			color = PURPLE;
		else if (game->map.grid[y][x] == 'D')
			color = DARKPINK;
		if (game->map.grid[y][x] == '1' || game->map.grid[y][x] == '0'
				|| game->map.grid[y][x] == 'D'
				|| game->map.grid[y][x] == 'O')
			ft_draw_square_map(game, game->screen_x, game->screen_y, color);
		x++;
	}
}
