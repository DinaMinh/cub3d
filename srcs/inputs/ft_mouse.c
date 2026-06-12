/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mouse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 11:13:09 by dminh             #+#    #+#             */
/*   Updated: 2026/06/12 11:39:30 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_initial_mouse_pos(t_game *game)
{
	mlx_mouse_hide(game->mlx_ptr, game->win_ptr);
	mlx_mouse_move(game->mlx_ptr, game->win_ptr, W_WIDTH / 2, W_HEIGHT / 2);
}

int	ft_mouse(int x, int y, t_game *game)
{
	int	delta_x;

	mlx_mouse_get_pos(game->mlx_ptr, game->win_ptr, &x, &y);
	delta_x = x - (W_WIDTH / 2);
	if (delta_x != 0)
	{
		game->player.angle += (float)delta_x * MOUSE_ROTATION;
		if (game->player.angle < 0)
			game->player.angle += 2 * M_PI;
		if (game->player.angle > 2 * M_PI)
			game->player.angle -= 2 * M_PI;
		game->player.dir_x = cos(game->player.angle);
		game->player.dir_y = sin(game->player.angle);
		mlx_mouse_move(game->mlx_ptr, game->win_ptr, W_WIDTH / 2, W_HEIGHT / 2);
	}
	return (0);
}
