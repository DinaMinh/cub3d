/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 16:06:32 by dminh             #+#    #+#             */
/*   Updated: 2026/06/08 16:37:45 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_set_orientation(t_game *game, int i, int j)
{
	if (game->map.grid[i][j] == 'W')
	{
		game->player.angle = WEST;
		game->map.grid[i][j] = '0';
	}
	else if (game->map.grid[i][j] == 'E')
	{
		game->player.angle = EAST;
		game->map.grid[i][j] = '0';
	}
	else if (game->map.grid[i][j] == 'N')
	{
		game->player.angle = NORTH;
		game->map.grid[i][j] = '0';
	}
	else if (game->map.grid[i][j] == 'S')
	{
		game->player.angle = SOUTH;
		game->map.grid[i][j] = '0';
	}
}

void	ft_starting_orientation(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map.grid[i])
	{
		j = 0;
		while (game->map.grid[i][j])
		{
			if (game->map.grid[i][j] == 'W' || game->map.grid[i][j] == 'S'
					|| game->map.grid[i][j] == 'E' || game->map.grid[i][j] == 'N')
			{
				game->player.pos_x = j * TILES + TILES / 2;
				game->player.pos_y = i * TILES + TILES / 2;
				ft_set_orientation(game, i, j);
				break;
			}
			j++;
		}
		i++;
	}
}

void	ft_init_texture(t_game *game)
{
	int	width = 32;
	int	height = 32;
	game->west.img = mlx_xpm_file_to_image(game->mlx_ptr, game->map.we_tex_path, &width, &height);
	game->west.addr = mlx_get_data_addr(game->west.img, &game->west.bits_per_pixel, &game->west.line_length, &game->west.endian);
}

unsigned int	ft_pixel_color(t_textures *texture, int x, int y)
{
	char	*dst;

	dst = texture->addr + (y * texture->line_length
			+ x * (texture->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	ft_game(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		exit(EXIT_FAILURE);
	game->win_ptr = mlx_new_window(game->mlx_ptr, W_WIDTH, W_HEIGHT, "cub3D");
	if (!game->win_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		exit(EXIT_FAILURE);
	}
	ft_init_texture(game);
	mlx_hook(game->win_ptr, DestroyNotify, StructureNotifyMask, (int (*)())(void(*)(void))ft_click_cross, game);
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, (int (*)())(void(*)(void))ft_input, game);
	mlx_hook(game->win_ptr, KeyRelease, KeyReleaseMask, (int (*)())(void(*)(void))ft_key_release, game);
	game->player.dir_x = cos(game->player.angle);
	game->player.dir_y = sin(game->player.angle);
	game->img = mlx_new_image(game->mlx_ptr, W_WIDTH, W_HEIGHT);
	game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel, &game->line_length, &game->endian);
	ft_draw_rays(game);
	ft_draw_map(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img, 0, 0);
	mlx_loop_hook(game->mlx_ptr, (int(*)())(void(*)())ft_game_hook, game);
	mlx_loop(game->mlx_ptr);
}
