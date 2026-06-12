/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_door_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 12:18:05 by dminh             #+#    #+#             */
/*   Updated: 2026/06/12 12:18:15 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_set_door_hori_rays(t_game *game)
{
	game->ray.is_door = true;
	if (game->ray.door_t_h == MASSIVE)
	{
		game->ray.door_hx = game->ray.x;
		game->ray.door_hy = game->ray.y;
		game->ray.door_t_h = ft_dist(game, game->ray.door_hx,
				game->ray.door_hy);
	}
	game->ray.x += game->ray.x_offset;
	game->ray.y += game->ray.y_offset;
	game->ray.dof++;
}

void	ft_set_door_vert_rays(t_game *game)
{
	game->ray.is_door = true;
	if (game->ray.door_t_v == MASSIVE)
	{
		game->ray.door_vx = game->ray.x;
		game->ray.door_vy = game->ray.y;
		game->ray.door_t_v = ft_dist(game, game->ray.door_vx,
				game->ray.door_vy);
	}
	game->ray.x += game->ray.x_offset;
	game->ray.y += game->ray.y_offset;
	game->ray.dof++;
}
