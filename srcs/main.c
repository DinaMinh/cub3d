/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 13:46:53 by dminh             #+#    #+#             */
/*   Updated: 2026/05/26 10:32:06 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map[6][6] =
{
	{1, 1, 1, 1, 1, 1},
	{1, 0, 1, 0, 0, 1},
	{1, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1},
};

int	ft_click_cross(t_game *game)
{
	mlx_destroy_image(game->mlx_ptr, game->img);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

void	ft_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > 720 || y < 0 || y > 1280)
		return ;
	dst = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_draw_square(t_game *game, int x, int y, int width)
{
	int	i;
	int	j;

	i = 0;
	while (i < width)
	{
		j = 0;
		while (j < width)
		{
			ft_pixel_put(game, x + j, y + i, YELLOW);
			j++;
		}
		i++;
	}
}

void	ft_draw_angle(t_game *game)
{
	float x;
	float y;
	int	i;

	x = game->player.pos_x;
	y = game->player.pos_y;
	i = 0;
	while (i < 20)
	{
		ft_pixel_put(game, x, y, RED);
		ft_pixel_put(game, x - 1, y, RED);
		ft_pixel_put(game, x, y + 1, RED);
		x += game->player.dir_x; 
		y += game->player.dir_y;
		i++;
	}
}

void	ft_draw_square_map(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILES - 1)
	{
		j = 0;
		while (j < TILES - 1)
		{
			ft_pixel_put(game, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	ft_draw_map(t_game *game)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < 6)
	{
		x = 0;
		while (x < 6)
		{
			if (map[y][x] == 1)
				color = WHITE;
			else
				color = PURPLE;
			ft_draw_square_map(game, x * TILES, y * TILES, color);
			x++;
		}
		y++;
	}
}

int	main(void)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(game));
	game.player.pos_x = 300;
	game.player.pos_y = 300;
	game.mlx_ptr = mlx_init();
	if (!game.mlx_ptr)
		return (EXIT_FAILURE);
	game.win_ptr = mlx_new_window(game.mlx_ptr, 1280, 720, "cub3D");
	if (!game.win_ptr)
	{
		mlx_destroy_display(game.mlx_ptr);
		return (EXIT_FAILURE);
	}
	mlx_hook(game.win_ptr, DestroyNotify, StructureNotifyMask, (int (*)())(void(*)(void))ft_click_cross, &game);
	mlx_hook(game.win_ptr, KeyPress, KeyPressMask, (int (*)())(void(*)(void))ft_input, &game);
	game.player.dir_x = cos(game.player.angle);
	game.player.dir_y = sin(game.player.angle);
	game.img = mlx_new_image(game.mlx_ptr, 1280, 720);
	game.addr = mlx_get_data_addr(game.img, &game.bits_per_pixel, &game.line_length, &game.endian);
	ft_draw_map(&game);
	ft_draw_angle(&game);
	ft_draw_square(&game, game.player.pos_x - SPEED, game.player.pos_y - SPEED, 10);
	ft_draw_rays(&game);
	mlx_put_image_to_window(game.mlx_ptr, game.win_ptr, game.img, 0, 0);
	mlx_loop(game.mlx_ptr);
	return (0);
}
