/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 11:59:27 by dminh             #+#    #+#             */
/*   Updated: 2026/06/12 12:06:36 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_raycasting(t_game *game)
{
	float	step;
	float	tex_y;
	int		tex_x;

	step = (float)TILES / game->ray.line_h;
	tex_y = 0;
	tex_x = 0;
	if (ft_check_door(game, &tex_x))
		;
	else
		ft_check_wall_face(game, &tex_x);
	ft_door_anim(game);
	ft_draw_walls(game, tex_x, tex_y, step);
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
