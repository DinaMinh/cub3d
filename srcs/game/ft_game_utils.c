/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 10:54:19 by dminh             #+#    #+#             */
/*   Updated: 2026/06/12 10:28:39 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

long long	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + (tv.tv_usec / 1000));
}

unsigned int	ft_pixel_color(t_textures *texture, int x, int y)
{
	char	*dst;

	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x >= TILES)
		x = TILES - 1;
	if (y >= TILES)
		y = TILES - 1;
	dst = texture->addr + (y * texture->line_length
			+ x * (texture->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	ft_get_fov(t_game *game)
{
	game->ray.fov = FOV * (M_PI / 180.0);
	game->ray.angle_step = game->ray.fov / W_WIDTH;
}
