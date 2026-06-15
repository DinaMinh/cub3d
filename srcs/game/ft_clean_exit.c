/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 10:44:05 by dminh             #+#    #+#             */
/*   Updated: 2026/06/15 13:54:32 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_destroy_textures(t_game *game)
{
	if (game->north.img)
		mlx_destroy_image(game->mlx_ptr, game->north.img);
	if (game->south.img)
		mlx_destroy_image(game->mlx_ptr, game->south.img);
	if (game->west.img)
		mlx_destroy_image(game->mlx_ptr, game->west.img);
	if (game->east.img)
		mlx_destroy_image(game->mlx_ptr, game->east.img);
	if (game->door.img)
		mlx_destroy_image(game->mlx_ptr, game->door.img);
	if (game->d_anim.frame1.img)
		mlx_destroy_image(game->mlx_ptr, game->d_anim.frame1.img);
	if (game->d_anim.frame2.img)
		mlx_destroy_image(game->mlx_ptr, game->d_anim.frame2.img);
	if (game->sword.img)
		mlx_destroy_image(game->mlx_ptr, game->sword.img);
	if (game->sword_anim.frame1.img)
		mlx_destroy_image(game->mlx_ptr, game->sword_anim.frame1.img);
	if (game->sword_anim.frame2.img)
		mlx_destroy_image(game->mlx_ptr, game->sword_anim.frame2.img);
	if (game->img)
		mlx_destroy_image(game->mlx_ptr, game->img);
}

void	ft_free_path(t_game *game)
{
	if (game->map.no_tex_path)
		free(game->map.no_tex_path);
	if (game->map.so_tex_path)
		free(game->map.so_tex_path);
	if (game->map.we_tex_path)
		free(game->map.we_tex_path);
	if (game->map.ea_tex_path)
		free(game->map.ea_tex_path);
}

int	ft_clean_exit(t_game *game, int return_value)
{
	int	i;

	i = 0;
	if (game->map.grid)
	{
		while (game->map.grid[i])
			free(game->map.grid[i++]);
		free(game->map.grid);
	}
	ft_free_path(game);
	if (game->map.raw_map)
		ft_lstclear(&game->map.raw_map, free);
	ft_destroy_textures(game);
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	exit(return_value);
	return (return_value);
}

int	ft_click_cross(t_game *game)
{
	return (ft_clean_exit(game, EXIT_SUCCESS));
}
