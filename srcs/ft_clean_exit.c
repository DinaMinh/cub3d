/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 10:44:05 by dminh             #+#    #+#             */
/*   Updated: 2026/06/09 10:44:05 by dminh            ###   ########.fr       */
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
	if (game->img)
		mlx_destroy_image(game->mlx_ptr, game->img);
}

int	ft_clean_exit(t_game *game)
{
	int	i;

	i = 0;
	if (game->map.grid)
	{
		while (game->map.grid[i])
			free(game->map.grid[i++]);
		free(game->map.grid);
	}
	if (game->map.no_tex_path)
		free(game->map.no_tex_path);
	if (game->map.so_tex_path)
		free(game->map.so_tex_path);
	if (game->map.we_tex_path)
		free(game->map.we_tex_path);
	if (game->map.ea_tex_path)
		free(game->map.ea_tex_path);
	if (game->map.raw_map)
		ft_lstclear(&game->map.raw_map, free);
	ft_destroy_textures(game);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

int	ft_click_cross(t_game *game)
{
	return (ft_clean_exit(game));
}
