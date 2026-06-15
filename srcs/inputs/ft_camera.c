/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_camera.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 10:36:52 by dminh             #+#    #+#             */
/*   Updated: 2026/06/10 11:08:46 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_camera(int keysym, t_game *game)
{
	if (keysym == XK_Left)
	{
		game->player.angle -= CAM_ANGLE;
		if (game->player.angle < 0)
			game->player.angle += 2 * M_PI;
	}
	else
	{
		game->player.angle += CAM_ANGLE;
		if (game->player.angle > 2 * M_PI)
			game->player.angle -= 2 * M_PI;
	}
	game->player.dir_x = cos(game->player.angle);
	game->player.dir_y = sin(game->player.angle);
}
