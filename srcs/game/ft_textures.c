/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textures.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 10:25:32 by dminh             #+#    #+#             */
/*   Updated: 2026/06/12 11:51:45 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_init_wall(t_game *game, int width, int height)
{
	game->north.img = mlx_xpm_file_to_image(game->mlx_ptr,
			game->map.no_tex_path, &width, &height);
	game->south.img = mlx_xpm_file_to_image(game->mlx_ptr,
			game->map.so_tex_path, &width, &height);
	game->west.img = mlx_xpm_file_to_image(game->mlx_ptr,
			game->map.we_tex_path, &width, &height);
	game->east.img = mlx_xpm_file_to_image(game->mlx_ptr,
			game->map.ea_tex_path, &width, &height);
	if (!game->north.img || !game->south.img || !game->west.img
		|| !game->east.img)
		ft_clean_exit(game, EXIT_FAILURE);
	game->north.addr = mlx_get_data_addr(game->north.img,
			&game->north.bits_per_pixel, &game->north.line_length,
			&game->north.endian);
	game->south.addr = mlx_get_data_addr(game->south.img,
			&game->south.bits_per_pixel, &game->south.line_length,
			&game->south.endian);
	game->west.addr = mlx_get_data_addr(game->west.img,
			&game->west.bits_per_pixel, &game->west.line_length,
			&game->west.endian);
	game->east.addr = mlx_get_data_addr(game->east.img,
			&game->east.bits_per_pixel, &game->east.line_length,
			&game->east.endian);
}

static void	ft_init_door(t_game *game, int width, int height)
{
	game->door.img = mlx_xpm_file_to_image(game->mlx_ptr, "./texture/door.xpm",
			&width, &height);
	game->d_anim.frame1.img = mlx_xpm_file_to_image(game->mlx_ptr,
			"./texture/d_anim1.xpm", &width, &height);
	game->d_anim.frame2.img = mlx_xpm_file_to_image(game->mlx_ptr,
			"./texture/d_anim2.xpm", &width, &height);
	if (!game->door.img || !game->d_anim.frame1.img || !game->d_anim.frame2.img)
		ft_clean_exit(game, EXIT_FAILURE);
	game->door.addr = mlx_get_data_addr(game->door.img,
			&game->door.bits_per_pixel, &game->door.line_length,
			&game->door.endian);
	game->d_anim.frame1.addr = mlx_get_data_addr(game->d_anim.frame1.img,
			&game->d_anim.frame1.bits_per_pixel,
			&game->d_anim.frame1.line_length, &game->d_anim.frame1.endian);
	game->d_anim.frame2.addr = mlx_get_data_addr(game->d_anim.frame2.img,
			&game->d_anim.frame2.bits_per_pixel,
			&game->d_anim.frame2.line_length, &game->d_anim.frame2.endian);
}

static void	ft_init_sword(t_game *game, int width, int height)
{
	game->sword.img = mlx_xpm_file_to_image(game->mlx_ptr,
			"./texture/sword.xpm", &width, &height);
	game->sword_anim.frame1.img = mlx_xpm_file_to_image(game->mlx_ptr,
			"./texture/sword_hit1.xpm", &width, &height);
	game->sword_anim.frame2.img = mlx_xpm_file_to_image(game->mlx_ptr,
			"./texture/sword_hit2.xpm", &width, &height);
	if (!game->sword.img || !game->sword_anim.frame1.img
		|| !game->sword_anim.frame2.img)
		ft_clean_exit(game, EXIT_FAILURE);
	game->sword.addr = mlx_get_data_addr(game->sword.img,
			&game->sword.bits_per_pixel, &game->sword.line_length,
			&game->sword.endian);
	game->sword_anim.frame1.addr
		= mlx_get_data_addr(game->sword_anim.frame1.img,
			&game->sword_anim.frame1.bits_per_pixel,
			&game->sword_anim.frame1.line_length,
			&game->sword_anim.frame1.endian);
	game->sword_anim.frame2.addr
		= mlx_get_data_addr(game->sword_anim.frame2.img,
			&game->sword_anim.frame2.bits_per_pixel,
			&game->sword_anim.frame2.line_length,
			&game->sword_anim.frame2.endian);
}

void	ft_init_texture(t_game *game)
{
	ft_init_wall(game, TILES, TILES);
	ft_init_door(game, TILES, TILES);
	ft_init_sword(game, TILES / 2, TILES / 2);
	game->img = mlx_new_image(game->mlx_ptr, W_WIDTH, W_HEIGHT);
	game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel,
			&game->line_length, &game->endian);
}
