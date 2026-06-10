/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 10:54:19 by dminh             #+#    #+#             */
/*   Updated: 2026/06/09 10:54:33 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

long long	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + (tv.tv_usec / 1000));
}

void	ft_init_texture(t_game *game)
{
	int	width = TILES;
	int	height = TILES;
	game->north.img = mlx_xpm_file_to_image(game->mlx_ptr, game->map.no_tex_path, &width, &height);
	game->south.img = mlx_xpm_file_to_image(game->mlx_ptr, game->map.so_tex_path, &width, &height);
	game->west.img = mlx_xpm_file_to_image(game->mlx_ptr, game->map.we_tex_path, &width, &height);
	game->east.img = mlx_xpm_file_to_image(game->mlx_ptr, game->map.ea_tex_path, &width, &height);
	width /= 2;
	height /= 2;
	game->sword.img = mlx_xpm_file_to_image(game->mlx_ptr, "./texture/sword.xpm", &width, &height);
	if (!game->north.img || !game->south.img || !game->west.img || !game->east.img
			|| !game->sword.img)
		ft_clean_exit(game);
	game->north.addr = mlx_get_data_addr(game->north.img, &game->north.bits_per_pixel, &game->north.line_length, &game->north.endian);
	game->south.addr = mlx_get_data_addr(game->south.img, &game->south.bits_per_pixel, &game->south.line_length, &game->south.endian);
	game->west.addr = mlx_get_data_addr(game->west.img, &game->west.bits_per_pixel, &game->west.line_length, &game->west.endian);
	game->east.addr = mlx_get_data_addr(game->east.img, &game->east.bits_per_pixel, &game->east.line_length, &game->east.endian);
	game->sword.addr = mlx_get_data_addr(game->sword.img, &game->sword.bits_per_pixel, &game->sword.line_length, &game->sword.endian);
}

unsigned int	ft_pixel_color(t_textures *texture, int x, int y)
{
	char	*dst;

	// FIX: Prevent negative coordinates
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
		
	// FIX: Prevent coordinates exceeding the texture width/height
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
